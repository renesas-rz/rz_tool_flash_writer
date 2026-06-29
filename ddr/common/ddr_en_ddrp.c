/*
 * Copyright (c) 2020-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// include
#include "common.h"
#include <ddr_internal.h>
#include <cpg.h>
#include "cpudrv.h"
#include "ddr.h"
#include "ddrcheck.h"

#define	CEIL(a, div)	(((a) + ((div) - 1)) / (div))
#define	_MIN(a, b)		((a) < (b) ? (a) : (b))
#define	_MAX(a, b)		((a) > (b) ? (a) : (b))

#define	MAX_BYTE_LANES		(2U)
#define	MAX_BEST_VREF_SAVED	(30U)
#define	VREF_SETP			(1U)

#define	INFO(...)
#define	VERBOSE(...)
#define ARRAY_SIZE(X) (sizeof(X)/(sizeof(X[0])))

#define DDR_BASE_ADDR		(0x40000000)
#define SRC_MEM_ADDR 		(0x50000000)
#define DDR_ACCESS_START_ADDR SRC_MEM_ADDR

#define DLY_CODE_MIN 		(-31)	// -11.78%
#define DLY_CODE_MAX 		32		// 29.80%
#define DLY_CODE_STEP 		(-1)
#define DLY_LEN				((DLY_CODE_MAX - DLY_CODE_MIN + 1) / - (DLY_CODE_STEP))
#define VREF_CODE_WR_STEP 	1
#define VREF_CODE_RD_MIN 	2		// 10.00%
#define VREF_CODE_RD_MAX 	126		// 90.96%
#define VREF_CODE_RD_STEP 	1
#define DQ_NUM 				16
#define RANK_NUM 			2

void panic(void)
{
	while(1);
}

uint32_t mc_odt_pins_tbl[4];
uint32_t mc_mr1_tbl[2];
uint32_t mc_mr2_tbl[2];
uint32_t mc_mr5_tbl[2];
uint32_t mc_mr6_tbl[2];
uint32_t mc_phy_settings_tbl[MC_PHYSET_NUM][2];
uint32_t swizzle_mc_tbl[SWIZZLE_MC_NUM][2];
uint32_t swizzle_phy_tbl[SIZZLE_PHY_NUM][2];
char ddr_an_version[8];
uint32_t mc_init_tbl[MC_INIT_NUM][2];

/* Status of DDR Parameters initialized or not */
uint8_t f_ddr_param_initialized = 0;

typedef struct {
	uint32_t	scl_lanes;
	uint8_t		byte_lanes;
	uint8_t		cs_bit;
	uint8_t		ranks;
	uint16_t	dram_clk_period;
	uint8_t		dram;
	uint64_t	addr[2];
	uint8_t		vref_code_write_min;
	uint8_t		vref_code_write_max;
	uint8_t		vref_code_write_step;
	uint8_t		vref_code_read_min;
	uint8_t		vref_code_read_max;
	uint8_t		vref_code_read_step;
	int8_t		dly_code_min;
	int8_t		dly_code_max;
	int8_t		dly_code_step;
	int8_t		dll_mas_dly;
	uint32_t	step_dly;
	int8_t		op_dq_trim[2][9];
	int8_t		ip_dq_trim[2][8];
} opne_eye_setting_t;
static opne_eye_setting_t setting;

// prototypes
static void disable_phy_clk(void);
static void program_mc1(uint8_t *lp_auto_entry_en);
static void program_phy1(uint32_t sl_lanes, uint32_t byte_lanes);
static void exec_trainingWRLVL(uint32_t sl_lanes);
static void exec_trainingVREF(uint32_t sl_lanes, uint32_t byte_lanes);
static void setup_vref_training_registers(uint8_t vref_value, uint8_t cs, uint8_t turn_on_off_vref_training);
static void write_mr(uint8_t cs, uint8_t mrw_sel, uint16_t mrw_data);
static void exec_trainingBITLVL(uint32_t sl_lanes);
static void opt_delay(uint32_t sl_lanes, uint32_t byte_lanes);
static void exec_trainingSL(uint32_t sl_lanes);
static void program_phy2(void);
static void program_mc2(void);
static void dram_write(uint64_t *addr, uint8_t rank_num,
						uint64_t *wr_data, uint32_t bytes, dmac_setting_t *dmac);
static void dram_read(uint64_t *addr, uint8_t rank_num,
						uint32_t *rd_buf, uint32_t *exp_data, uint32_t bytes, dmac_setting_t *dmac,
						uint16_t compareResult[][DLY_LEN], uint16_t dly);
static void drawResult(const uint8_t rank_num, const uint16_t compareResult[][DLY_LEN]);

#if (DDR_ECC_ENABLE == 1)
#define DDR_BASE_ADDRESS	0x40000000
#define TEST_BIT_NO			0
#define USER_WORD_DATA		0x5a5a5a5a5a5a5a5a
#define ECC_ERR_ADDRESS		0x60000000
static int ecc_force_ce_error(void);
static void ecc_prog_all0(uint64_t addr_start, uint64_t addr_end);
static void init_ecc(void);
#if (DDR_ECC_DETECT_CORRECT == 1)
char data_synd[] = {
			0xf4, 0xf1, 0xec, 0xea, 0xe9, 0xe6, 0xe5, 0xe3,
			0xdc, 0xda, 0xd9, 0xd6, 0xd5, 0xd3, 0xce, 0xcb,
			0xb5, 0xb0, 0xad, 0xab, 0xa8, 0xa7, 0xa4, 0xa2,
			0x9d, 0x9b, 0x98, 0x97, 0x94, 0x92, 0x8f, 0x8a,
			0x75, 0x70, 0x6d, 0x6b, 0x68, 0x67, 0x64, 0x62,
			0x5e, 0x5b, 0x58, 0x57, 0x54, 0x52, 0x4f, 0x4a,
			0x34, 0x31, 0x2c, 0x2a, 0x29, 0x26, 0x25, 0x23,
			0x1c, 0x1a, 0x19, 0x16, 0x15, 0x13, 0x0e, 0x0b
		  };
#endif
#endif

// main
void ddr_setup(opt_delay_flg_t runOptDelay)
{
	uint32_t	sl_lanes, byte_lanes;
	uint8_t		runBITLVL, runSL, runVREF;
	uint8_t		lp_auto_entry_en = 0;
	uint32_t	tmp;
	int i;

#if DDR_DEBUG
	PutStr("BL2: setup DDR (Rev. ", 0);
	PutStr(ddr_an_version, 0);
	PutStr(")", 1);
#endif

	// Step2 - Step11
	cpg_active_ddr(disable_phy_clk);
#if DDR_DEBUG
	PutStr("  Step1 - Step11 completed", 1);
#endif

	// Step12
	program_mc1(&lp_auto_entry_en);
#if DDR_DEBUG
	PutStr("  Step12 completed", 1);
#endif

	// Step13
	tmp = read_mc_reg(DDRMC_R019);
	sl_lanes	= ((tmp & 0x1) == 0) ? 3 : 1;
	byte_lanes	= ((tmp & 0x1) == 0) ? 2 : 1;
	tmp = read_mc_reg(DDRMC_R039);
	runBITLVL	= (tmp >> 20) & 0x1;
	runSL		= (tmp >> 21) & 0x1;
	runVREF		= (tmp >> 25) & 0x1;
#if DDR_DEBUG
	PutStr("  Step13 completed", 1);
#endif

	// Step14
	program_phy1(sl_lanes, byte_lanes);
#if DDR_DEBUG
	PutStr("  Step14 completed", 1);
#endif

	// Step15
	while ((read_phy_reg(DDRPHY_R42) & 0x00000003) != sl_lanes)
		;
#if DDR_DEBUG
	PutStr("  Step15 completed", 1);
#endif

	// Step16
	ddr_ctrl_reten_en_n(0);
	rmw_mc_reg(DDRMC_R007, 0xFFFFFEFF, 0x00000000);
	rmw_mc_reg(DDRMC_R001, 0xFEFFFFFF, 0x01000000);
	rmw_mc_reg(DDRMC_R000, 0xFFFFFFFE, 0x00000001);
	while ((read_mc_reg(DDRMC_R021) & 0x02000000) != 0x02000000)
		;
	rmw_phy_reg(DDRPHY_R74, 0xFFF7FFFF, 0x00080000);
	rmw_mc_reg(DDRMC_R029, 0xFF0000FF, 64 << 8);
	rmw_mc_reg(DDRMC_R027, 0xE00000FF, 111 << 8);
	rmw_mc_reg(DDRMC_R020, 0xFFFFFEFF, 0x00000100);
	udelay(1);
	rmw_phy_reg(DDRPHY_R74, 0xFFF7FFFF, 0x00000000);
#if DDR_DEBUG
	PutStr("  Step16 completed", 1);
#endif

	// Step17
	cpg_reset_ddr_mc();
	ddr_ctrl_reten_en_n(1);
#if DDR_DEBUG
	PutStr("  Step17 completed", 1);
#endif

	// Step18-19
	program_mc1(&lp_auto_entry_en);
#if DDR_DEBUG
	PutStr("  Step18 completed", 1);
	PutStr("  Step19 completed", 1);
#endif

	// Step20
	for (i = 0; i < ARRAY_SIZE(swizzle_mc_tbl); i++) {
		write_mc_reg(swizzle_mc_tbl[i][0], swizzle_mc_tbl[i][1]);
	}
	for (i = 0; i < ARRAY_SIZE(swizzle_phy_tbl); i++) {
		write_phy_reg(swizzle_phy_tbl[i][0], swizzle_phy_tbl[i][1]);
	}
#if DDR_DEBUG
	PutStr("  Step20 completed", 1);
#endif

	// Step21
	rmw_mc_reg(DDRMC_R000, 0xFFFFFFFE, 0x00000001);
#if DDR_DEBUG
	PutStr("  Step21 completed", 1);
#endif

	// Step22
	while ((read_mc_reg(DDRMC_R021) & 0x02000000) != 0x02000000)
		;
#if DDR_DEBUG
	PutStr("  Step22 completed", 1);
#endif

	// Step23
	rmw_mc_reg(DDRMC_R023, 0xFDFFFFFF, 0x02000000);
#if DDR_DEBUG
	PutStr("  Step23 completed", 1);
#endif

	// Step24
	exec_trainingWRLVL(sl_lanes);
#if DDR_DEBUG
	PutStr("  Step24 completed", 1);
#endif

	// Step25
	if (runVREF == 1){
		exec_trainingVREF(sl_lanes, byte_lanes);
#if DDR_DEBUG
		PutStr("  Step25 completed", 1);
#endif
	}
	else{
#if DDR_DEBUG
		PutStr("  Step25 Run VREF is skipped", 1);
#endif
	}

	// Step26
	if (runBITLVL == 1){
		exec_trainingBITLVL(sl_lanes);
#if DDR_DEBUG
		PutStr("  Step26 completed", 1);
#endif
	}
	else{
#if DDR_DEBUG
		PutStr("  Step26 Run BIT LEVEL is skipped", 1);
#endif
	}

	// Step27
	if (runOptDelay == 1){
		opt_delay(sl_lanes, byte_lanes);
#if DDR_DEBUG
		PutStr("  Step27 completed", 1);
#endif
	}
	else{
#if DDR_DEBUG
		PutStr("  Step27 Run Opt Delay is skipped", 1);
#endif
	}

	// Step28
	if (runSL == 1){
		exec_trainingSL(sl_lanes);
#if DDR_DEBUG
		PutStr("  Step28 completed", 1);
#endif
	}
	else{
#if DDR_DEBUG
		PutStr("  Step28 Run SL is skipped", 1);
#endif
	}

	// Step29
	program_phy2();
#if DDR_DEBUG
	PutStr("  Step29 completed", 1);
#endif

	// Step30
	program_mc2();
#if DDR_DEBUG
	PutStr("  Step30 completed", 1);
#endif

	// Step31 is skipped because ECC is unused.
#if (DDR_ECC_ENABLE == 1)
#if (DDR_ECC_DETECT_CORRECT == 1)
	NOTICE("BL2: ECC MODE: Error Detect and Correct\n");
#elif (DDR_ECC_DETECT == 1)
	NOTICE("BL2: ECC MODE: Error Detect\n");
#else
	NOTICE("BL2: ECC MODE: Enable\n");
#endif

	init_ecc();

	NOTICE("ECC INIT DONE\n");
#endif
#if DDR_DEBUG
	PutStr("  Step31 completed", 1);
#endif

	// Step32
	// let the auto_exit_en to be value|0x8
	// recommended value for "value" is 0x0
	rmw_mc_set_field(LP_AUTO_EXIT_EN_ADDR, LP_AUTO_EXIT_EN_WIDTH, LP_AUTO_EXIT_EN_OFFSET, 0x8);
	rmw_mc_set_field(LP_AUTO_ENTRY_EN_ADDR, LP_AUTO_ENTRY_EN_WIDTH, LP_AUTO_ENTRY_EN_OFFSET, lp_auto_entry_en);

#if (DDR_ECC_ENABLE == 1)
	// Extra step, test ECC CE function
	NOTICE("BL2: ECC CE function testing ....\n");
	if (ecc_force_ce_error())
		ERROR("DDR ECC Force CE FAILED\n");
	else
		NOTICE("OK\n");
#endif
#if DDR_DEBUG
	PutStr("  Step32 completed", 1);
	PutStr("DDR init completed", 1);
#endif
}

#if (DDR_ECC_ENABLE == 1)
#if (DDR_ECC_DETECT_CORRECT == 1)
static int ecc_force_ce_error(void)
{
	int ret;
	uint64_t err_addr;
	uint64_t *user_word;
	uint32_t tmp, synd, xor_check_code;
	uint32_t retry = 0xffffffU;
	uint32_t bak_DDRMC_R052;

	bak_DDRMC_R052 = read_mc_reg(DDRMC_R052);

	// make checkcode
	xor_check_code = (data_synd[0] << 8) | 1;
	user_word = (uint64_t *)ECC_ERR_ADDRESS;

	do {
		tmp = read_mc_reg(DDRMC_R020);
	} while (tmp & 1);

	rmw_mc_reg(DDRMC_R052, ~((0xff << 8) | 1), xor_check_code);

	*user_word = USER_WORD_DATA;
	flush_dcache_range((unsigned long)user_word, sizeof(uint64_t));
	(*(const volatile uint64_t *)user_word);

	rmw_mc_reg(DDRMC_R052, ~((0xff << 8) | 1), 0);

	do {
		tmp = read_mc_reg(DDRMC_R064);
	} while ((retry--) && !(tmp & 0xffffU));

	// out of retry or not CE
	if (!retry || !(tmp & 0x3)) {
		ERROR("DDR error: out of retry or not CE.\n");
		ret = -1;
		goto err;
	}

	// ack ecc int
	tmp = 0xffffU;
	write_mc_reg(DDRMC_R066, tmp);

	// check the error address
	err_addr = (uint64_t)(read_mc_reg(DDRMC_R054) & 0x3);
	err_addr = err_addr << 32;
	err_addr |= (uint64_t)read_mc_reg(DDRMC_R053);
	err_addr += DDR_BASE_ADDRESS;
	if (((uint64_t)user_word) != err_addr) {
		ret = -1;
		ERROR("DDR error: ECC error address mismatch.\n");
		goto err;
	}

	// check error synd
	synd = read_mc_reg(DDRMC_R054);
	synd = (synd >> 8) & 0xff;
	if (synd != (xor_check_code >> 8)) {
		ret = -1;
		ERROR("DDR error: ECC error synd mismatch.\n");
		goto err;
	}

	if ((*user_word ^ USER_WORD_DATA) != BIT(TEST_BIT_NO)) {
		ret = -1;
		ERROR("DDR error: ECC error data mismatch.\n");
		goto err;
	}

	write_mc_reg(DDRMC_R052, bak_DDRMC_R052);

	return 0;

err:
	write_mc_reg(DDRMC_R052, bak_DDRMC_R052);

	return ret;
}
#else
static int ecc_force_ce_error(void)
{
	return 0;
}
#endif

static void ecc_prog_all0(uint64_t addr_start, uint64_t addr_end)
{
	INFO("BL2: ECC prog all0 start\n");

	int i;
	uint32_t val;
	uint64_t addr, prog_size;
	uint32_t bak_lp_auto_entry_en, bak_in_order_accept;

	// 1
	addr = addr_start - DDR_BASE_ADDRESS;
	prog_size = addr_end - addr_start + 1;

	// 2
	bak_lp_auto_entry_en = read_mc_field(LP_AUTO_ENTRY_EN_ADDR, LP_AUTO_ENTRY_EN_WIDTH, LP_AUTO_ENTRY_EN_OFFSET);
	rmw_mc_set_field(LP_AUTO_ENTRY_EN_ADDR, LP_AUTO_ENTRY_EN_WIDTH, LP_AUTO_ENTRY_EN_OFFSET, 0x0);

	bak_in_order_accept = read_mc_field(IN_ORDER_ACCEPT_ADDR, IN_ORDER_ACCEPT_WIDTH, IN_ORDER_ACCEPT_OFFSET);
	rmw_mc_set_field(IN_ORDER_ACCEPT_ADDR, IN_ORDER_ACCEPT_WIDTH, IN_ORDER_ACCEPT_OFFSET, 0x1);

	// 3
	rmw_mc_set_field(BIST_DATA_CHECK_ADDR, BIST_DATA_CHECK_WIDTH, BIST_DATA_CHECK_OFFSET, 0x1);
	rmw_mc_set_field(BIST_ADDR_CHECK_ADDR, BIST_ADDR_CHECK_WIDTH, BIST_ADDR_CHECK_OFFSET, 0x0);
	rmw_mc_set_field(BIST_TEST_MODE_ADDR, BIST_TEST_MODE_WIDTH, BIST_TEST_MODE_OFFSET, 0x4);

	rmw_mc_set_field(BIST_DATA_PATTERN_0_ADDR, BIST_DATA_PATTERN_0_WIDTH, BIST_DATA_PATTERN_0_OFFSET, 0x0);
	rmw_mc_set_field(BIST_DATA_PATTERN_1_ADDR, BIST_DATA_PATTERN_1_WIDTH, BIST_DATA_PATTERN_1_OFFSET, 0x0);
	rmw_mc_set_field(INT_MASK_BIST_ADDR, INT_MASK_BIST_WIDTH, INT_MASK_BIST_OFFSET, 0x1);


	// 4
	for (i = 0 ; i < 34 ; i++) {
		if (((prog_size >> i) & 1) == 1) {
			rmw_mc_set_field(BIST_START_ADDRESS_0_ADDR, BIST_START_ADDRESS_0_WIDTH, BIST_START_ADDRESS_0_OFFSET, addr & 0xffffffff);
			rmw_mc_set_field(BIST_START_ADDRESS_1_ADDR, BIST_START_ADDRESS_1_WIDTH, BIST_START_ADDRESS_1_OFFSET, (addr >> 32) & 0x3);
			rmw_mc_set_field(ADDR_SPACE_ADDR, ADDR_SPACE_WIDTH, ADDR_SPACE_OFFSET, i);

			mdelay(10);

			rmw_mc_set_field(BIST_GO_ADDR, BIST_GO_WIDTH, BIST_GO_OFFSET, 1);
			do {

			} while (!(read_mc_field(INT_STATUS_BIST_ADDR, INT_STATUS_0_BIST_WIDTH, INT_STATUS_0_BIST_OFFSET)));

			rmw_mc_set_field(BIST_GO_ADDR, BIST_GO_WIDTH, BIST_GO_OFFSET, 0);

			rmw_mc_set_field(INT_ACK_BIST_ADDR, INT_ACK_0_BIST_WIDTH, INT_ACK_0_BIST_OFFSET, 1);
			do {

			} while (read_mc_field(INT_STATUS_BIST_ADDR, INT_STATUS_0_BIST_WIDTH, INT_STATUS_0_BIST_OFFSET));

			addr += (1 << i);
		}
	}

	// 5
	rmw_mc_set_field(INT_ACK_ECC_ADDR, INT_ACK_ECC_WIDTH, INT_ACK_ECC_OFFSET, 0xFFFF);

	do {
		val = read_mc_field(INT_STATUS_ECC_ADDR, INT_STATUS_ECC_WIDTH, INT_STATUS_ECC_OFFSET);
	} while (val != 0);

	// 6
	rmw_mc_set_field(INT_MASK_BIST_ADDR, INT_MASK_BIST_WIDTH, INT_MASK_BIST_OFFSET, 0x0);


	// 7
	rmw_mc_set_field(LP_AUTO_ENTRY_EN_ADDR, LP_AUTO_ENTRY_EN_WIDTH, LP_AUTO_ENTRY_EN_OFFSET, bak_lp_auto_entry_en);
	rmw_mc_set_field(IN_ORDER_ACCEPT_ADDR, IN_ORDER_ACCEPT_WIDTH, IN_ORDER_ACCEPT_OFFSET, bak_in_order_accept);
	INFO("BL2: ECC prog all0 done\n");
}

// follow DDRTOP_ApplicationNote_Rev01.14.excel
// capter SubProc->Init0_ECC
static void init_ecc(void)
{
	uint64_t addr_start, addr_end;
	uint32_t cs_val_upper, val;
	INFO("BL2: ECC init start\n");
	// 1. check DDR3/DDR3L/DDR4
	val = read_mc_reg(USER_DEF_REG_10_ADDR);
	val = (val >> 16) & 0xF;
	if (val == 2)
		addr_start = DDR_BASE_ADDRESS + 0x40;
	else
		addr_start = DDR_BASE_ADDRESS + 0x20;

	// 2
	cs_val_upper = read_mc_reg(CS_VAL_UPPER_0_ADDR);
	cs_val_upper = (cs_val_upper >> 16) & 0xffffU;
	val = read_mc_reg(CS_MAP_ADDR);
	val = (val >> 16) & 0x3;
	if (val == 0x3) {
		val = read_mc_reg(CS_VAL_UPPER_1_ADDR);
		val = (val >> 16) & 0xffffU;
		if (val > cs_val_upper) {
			cs_val_upper = val;
		}
	}
	addr_end = (uint64_t)(((cs_val_upper + 1) << 18) - 1) + DDR_BASE_ADDRESS;

	// 3
	// ECC_DISABLE_W_UC_ERR <= 1
	rmw_mc_set_field(ECC_DISABLE_W_UC_ERR_ADDR, ECC_DISABLE_W_UC_ERR_WIDTH, ECC_DISABLE_W_UC_ERR_OFFSET, 0x1);

	// mask ECC interrupt
	rmw_mc_set_field(INT_MASK_ECC_ADDR, INT_MASK_ECC_WIDTH, INT_MASK_ECC_OFFSET, 0x01CF);

	// 4. wait for 10 regACLK
	mdelay(10);

	// 5.prog_all0
	ecc_prog_all0(addr_start, addr_end);

	// 6.
	// unmask ECC interrupt
	rmw_mc_set_field(INT_MASK_ECC_ADDR, INT_MASK_ECC_WIDTH, INT_MASK_ECC_OFFSET, 0x0000);

	// ack ECC interrupt
	rmw_mc_set_field(INT_ACK_ECC_ADDR, INT_ACK_ECC_WIDTH, INT_ACK_ECC_OFFSET, 0x01CF);

	// ECC_DISABLE_W_UC_ERR = 0
	rmw_mc_set_field(ECC_DISABLE_W_UC_ERR_ADDR, ECC_DISABLE_W_UC_ERR_WIDTH, ECC_DISABLE_W_UC_ERR_OFFSET, 0x0000);

	mdelay(10);
	INFO("BL2: ECC init end\n");
}

static void program_mc1_ecc_en(void)
{
	uint32_t tmp = 0;
	uint16_t addr_diff[2], cs_size[2], cs_val_lower[2], row_start_val[2];
	int i, maxrow_cs;

	tmp = read_mc_reg(ECC_ENABLE_ADDR);
	tmp &= ~(0x3 << 24);
#if (DDR_ECC_DETECT_CORRECT == 1)
	tmp |= (0x3 << ECC_ENABLE_OFFSET);
#elif (DDR_ECC_DETECT == 1)
	tmp |= (0x2 << ECC_ENABLE_OFFSET);
#else
	tmp |= (1 << ECC_ENABLE_OFFSET);
#endif

	write_mc_reg(ECC_ENABLE_ADDR, tmp);
	rmw_mc_set_field(ADDR_COLLISION_MPM_DIS_ADDR, ADDR_COLLISION_MPM_DIS_WIDTH, ADDR_COLLISION_MPM_DIS_OFFSET, 1);
	rmw_mc_set_field(DISABLE_RD_INTERLEAVE_ADDR, DISABLE_RD_INTERLEAVE_WIDTH, DISABLE_RD_INTERLEAVE_OFFSET, 0);

	rmw_mc_set_field(IN_ORDER_ACCEPT_ADDR, IN_ORDER_ACCEPT_WIDTH, IN_ORDER_ACCEPT_OFFSET, 1);
	rmw_mc_set_field(SWAP_EN_ADDR, SWAP_EN_WIDTH, SWAP_EN_OFFSET, 0);


	addr_diff[0] = read_mc_field(BANK_DIFF_0_ADDR, BANK_DIFF_0_WIDTH, BANK_DIFF_0_OFFSET);
	addr_diff[0] += read_mc_field(COL_DIFF_0_ADDR, COL_DIFF_0_WIDTH, COL_DIFF_0_OFFSET);
	addr_diff[0] += read_mc_field(ROW_DIFF_0_ADDR, ROW_DIFF_0_WIDTH, ROW_DIFF_0_OFFSET);

	addr_diff[1] = read_mc_field(BANK_DIFF_1_ADDR, BANK_DIFF_1_WIDTH, BANK_DIFF_1_OFFSET);
	addr_diff[1] += read_mc_field(COL_DIFF_1_ADDR, COL_DIFF_1_WIDTH, COL_DIFF_1_OFFSET);
	addr_diff[1] += read_mc_field(ROW_DIFF_1_ADDR, ROW_DIFF_1_WIDTH, ROW_DIFF_1_OFFSET);

	for (i = 0; i < 2; i++) {
		cs_size[i] = (0xDFFF >> 1) >> addr_diff[i];
	}

	if (cs_size[0] >= cs_size[1]) {
		maxrow_cs = 0;
	} else {
		maxrow_cs = 1;
	}

	cs_val_lower[maxrow_cs] = 0x0000;
	cs_val_lower[(maxrow_cs + 1) % 2] = cs_val_lower[maxrow_cs] + cs_size[maxrow_cs] + 1;

	rmw_mc_set_field(CS_VAL_LOWER_0_ADDR, CS_VAL_LOWER_0_WIDTH, CS_VAL_LOWER_0_OFFSET, cs_val_lower[0]);
	rmw_mc_set_field(CS_VAL_UPPER_0_ADDR, CS_VAL_UPPER_0_WIDTH, CS_VAL_UPPER_0_OFFSET, (cs_val_lower[0] + cs_size[0]));

	tmp = read_mc_field(CS_MAP_ADDR, CS_MAP_WIDTH, CS_MAP_OFFSET);
	if (tmp == 0x3) {
		rmw_mc_set_field(CS_VAL_LOWER_1_ADDR, CS_VAL_LOWER_1_WIDTH, CS_VAL_LOWER_1_OFFSET, cs_val_lower[1]);
		rmw_mc_set_field(CS_VAL_UPPER_1_ADDR, CS_VAL_UPPER_1_WIDTH, CS_VAL_UPPER_1_OFFSET, (cs_val_lower[1] + cs_size[1]));
	}

	row_start_val[maxrow_cs] = 0x0;
	i = (maxrow_cs + 1) % 2;
	if (cs_size[i] == cs_size[maxrow_cs]) {
		row_start_val[i] = 0x1;
	} else if (cs_size[i] == (cs_size[maxrow_cs] >> 1)) {
		row_start_val[i] = 0x2;
	} else if (cs_size[i] == (cs_size[maxrow_cs] >> 2)) {
		row_start_val[i] = 0x4;
	} else {
		row_start_val[i] = 0x0;
	}

	rmw_mc_set_field(ROW_START_VAL_0_ADDR, ROW_START_VAL_0_WIDTH, ROW_START_VAL_0_OFFSET, row_start_val[0]);
	rmw_mc_set_field(ROW_START_VAL_1_ADDR, ROW_START_VAL_1_WIDTH, ROW_START_VAL_1_OFFSET, row_start_val[1]);
}
#endif // (DDR_ECC_ENABLE == 1)

static void disable_phy_clk(void)
{
	// Initialization Step9
	write_phy_reg(DDRPHY_R77, 0x00000200);
	write_phy_reg(DDRPHY_R78, 0x00010001);
}

static void program_mc1(uint8_t *lp_auto_entry_en)
{
	int i;

	// Step1
	for (i = 0; i < ARRAY_SIZE(mc_init_tbl); i++) {
		if (mc_init_tbl[i][0] == DDRMC_R006) {
			*lp_auto_entry_en = mc_init_tbl[i][1] & 0xF;
			write_mc_reg(DDRMC_R006, mc_init_tbl[i][1] & 0xFFFFFFF0);
		} else {
			write_mc_reg(mc_init_tbl[i][0], mc_init_tbl[i][1]);
		}
	}

	// Step2
	rmw_mc_reg(DDRMC_R025, 0xFCFFFFFF, mc_odt_pins_tbl[0] << 24);
	rmw_mc_reg(DDRMC_R026, 0xFFFFFCFF, mc_odt_pins_tbl[1] << 8);
	rmw_mc_reg(DDRMC_R025, 0xFFFCFFFF, mc_odt_pins_tbl[2] << 16);
	rmw_mc_reg(DDRMC_R026, 0xFFFFFFFC, mc_odt_pins_tbl[3] << 0);

	// Step3
	rmw_mc_reg(DDRMC_R009, ~(mc_mr1_tbl[0]), mc_mr1_tbl[1]);
	rmw_mc_reg(DDRMC_R011, ~(mc_mr1_tbl[0]), mc_mr1_tbl[1]);

	// Step4
	rmw_mc_reg(DDRMC_R010, ~(mc_mr2_tbl[0]), mc_mr2_tbl[1]);
	rmw_mc_reg(DDRMC_R012, ~(mc_mr2_tbl[0]), mc_mr2_tbl[1]);

	// Step5
	rmw_mc_reg(DDRMC_R015, ~(mc_mr5_tbl[0]), mc_mr5_tbl[1]);
	rmw_mc_reg(DDRMC_R016, ~(mc_mr5_tbl[0]), mc_mr5_tbl[1]);

	// Step6
	rmw_mc_reg(DDRMC_R017, ~(mc_mr6_tbl[0]), mc_mr6_tbl[1]);
	rmw_mc_reg(DDRMC_R018, ~(mc_mr6_tbl[0]), mc_mr6_tbl[1]);

	// Step7
	for (i = 0; i < ARRAY_SIZE(mc_phy_settings_tbl); i++) {
		write_mc_reg(mc_phy_settings_tbl[i][0], mc_phy_settings_tbl[i][1]);
	}

	// Step8 is skipped because ECC is unused.
#if (DDR_ECC_ENABLE == 1)
	program_mc1_ecc_en();
#endif
}

static void lpddr4_combo_io_cal(void)
{
	/* Step37-1 */
	uint32_t tmp;
	uint8_t dram = (read_mc_reg(USER_DEF_REG_10_ADDR) >> 16) & 0xF;

	// Step37-2
	rmw_phy_reg(UNIQUIFY_IO_2, 0xFF800000, 0x00000000);

	// Step37-3
	switch (dram) {
	case 0:
		tmp = 0x00003200;
		break;
	case 1:
		tmp = 0x00005200;
		break;
	case 2:
		tmp = 0x08009200;
		break;
	default:
		tmp = 0x00000000;
		break;
	}
	write_phy_reg(UNIQUIFY_IO_3, tmp);
	write_phy_reg(UNIQUIFY_IO_1, 0x00000002);

	while ((read_phy_reg(UNIQUIFY_IO_1) & 0x00000008) != 0x00000008)
		;

	write_phy_reg(UNIQUIFY_IO_1, 0x00000000);
	udelay(100);

	// Step37-4
	switch (dram) {
	case 0:
	case 1:
		tmp = 0x00041200;
		break;
	case 2:
		tmp = 0x08101300;
		break;
	default:
		tmp = 0x00000000;
		break;
	}
	write_phy_reg(UNIQUIFY_IO_3, tmp);
	write_phy_reg(UNIQUIFY_IO_1, 0x00000001);
	while ((read_phy_reg(UNIQUIFY_IO_1) & 0x00000004) != 0x00000004)
		;

	rmw_phy_reg(UNIQUIFY_IO_1, 0xFFFFFFEF, 0x00000010);
	rmw_phy_reg(UNIQUIFY_IO_1, 0xFFFFFFEF, 0x00000000);
	udelay(1);
}

static void program_phy1(uint32_t sl_lanes, uint32_t byte_lanes)
{
	uint32_t i;
	uint16_t dram_clk_period;
	int8_t extra_addrctrl_dly;
	int8_t ofs_dlls_trim_1, ofs_dlls_trim_3;
	uint8_t dram;
	uint8_t odt_wr_map_cs0, odt_rd_map_cs0;
	uint8_t CL, CWL, AL, PL, RL, WL;
	uint32_t mr1, mr1_wl, mr1_wl_mask;
	uint32_t mr2, mr2_wl, mr2_wl_mask;
	uint8_t clk_drive, dq_dqs_drive, dq_dqs_term, vref_value, vref_ca_value, adrctrl_drive;
	uint8_t read_lat, trim_lat;

	/*
	 * Unused
	 * int8_t dll_mas_dly
	 * uint8_t core_clk_margin_win_a, core_clk_margin_win_b;
	 * uint8_t incr_winA_val, incr_winB_val;
	 * uint8_t soc_dq_drive, soc_dq_odt;
	 * uint8_t dram_dq_drive, dram_dq_odt_wr1, dram_dq_odt_rd2, dram_dq_odt_wr2;
	 */
	uint8_t swap_phase;
	uint32_t tmp;

	// Step1
	tmp = read_mc_reg(USER_DEF_REG_10_ADDR);
	dram_clk_period = (tmp >> 0) & 0xFFFF;
	dram = (tmp >> 16) & 0xF;

	odt_wr_map_cs0 = read_mc_field(ODT_WR_MAP_CS0_ADDR, ODT_WR_MAP_CS0_WIDTH, ODT_WR_MAP_CS0_OFFSET);
	odt_rd_map_cs0 = read_mc_field(ODT_RD_MAP_CS0_ADDR, ODT_RD_MAP_CS0_WIDTH, ODT_RD_MAP_CS0_OFFSET);

	// Step2
	CL = read_mc_field(CASLAT_LIN_ADDR, 0x5, CASLAT_LIN_OFFSET + 1);
	CWL = read_mc_field(WRLAT_ADDR, WRLAT_WIDTH, WRLAT_OFFSET);

	AL =  read_mc_field(ADDITIVE_LAT_ADDR, ADDITIVE_LAT_WIDTH, ADDITIVE_LAT_OFFSET);
	PL =  read_mc_field(CA_PARITY_LAT_ADDR, CA_PARITY_LAT_WIDTH, CA_PARITY_LAT_OFFSET);

	RL = CL + AL + PL;
	WL = CWL + AL + PL;

	// Step3
	mr1 = read_mc_reg(MR1_DATA_0_ADDR) & 0xFFFF;
	mr2 = read_mc_reg(MR2_DATA_0_ADDR) & 0xFFFF;

	if (dram == 2) {
		// DDR4
		mr1_wl_mask = (0x1 << 7) | (0x7 << 8) ;	// 0x78
		tmp = ((mr2 >> 9) & 0x7);
		switch (tmp) {
		case 0:
			mr1_wl = mr1 | (1<<7);
			break;
		case 1:
			mr1_wl = (mr1 & (0xFFFF ^ mr1_wl_mask)) | (1 << 7) | (0x2 << 8);
			break;
		case 2:
			mr1_wl = (mr1 & (0xFFFF ^ mr1_wl_mask)) | (1 << 7) | (0x4 << 8);
			break;
		case 4:
			mr1_wl = (mr1 & (0xFFFF ^ mr1_wl_mask)) | (1 << 7) | (0x6 << 8);
			break;
		default:
			panic();
		}

		mr2_wl_mask = 0x7 << 9;
		mr2_wl = (mr2 & (0xFFFF ^ mr2_wl_mask)) | (0x0 << 9);
	} else {
		// DDR3L, DDR3
		mr1_wl_mask = (0x1 << 9) | (0x1 << 7) | (0x1 << 6) | (0x1 << 2);
		tmp = ((mr2>>9) & 0x3);
		switch (tmp) {
		case 0:
			mr1_wl = mr1 | (1 << 7);
			break;
		case 1:
			mr1_wl = (mr1 & (0xFFFF ^ mr1_wl_mask)) | (1 << 7) | (0 << 9) | (0 << 6) | (1 << 2);
			break;
		case 2:
			mr1_wl = (mr1 & (0xFFFF ^ mr1_wl_mask)) | (1 << 7) | (0 << 9) | (1 << 6) | (0 << 2);
			break;
		default:
			panic();
		}

		mr2_wl_mask = 0x3 << 9;
		mr2_wl = (mr2 & (0xFFFF ^ mr2_wl_mask)) | (0x0 << 9);
	}

	// Step4
	tmp = read_mc_reg(USER_DEF_REG_11_ADDR);
	clk_drive = tmp & 0xF;
	dq_dqs_drive = (tmp >> 4) & 0xF;
	dq_dqs_term = (tmp >> 8) & 0xF;
	adrctrl_drive = (tmp >> 12) & 0xF;
	vref_value = (tmp >> 16) & 0xFF;
	vref_ca_value = (tmp >> 24) & 0xFF;

	/*
	 * Unused
	 * tmp = read_mc_reg(USER_DEF_REG_12_ADDR);
	 * soc_dq_drive = (tmp >> 0) & 0xFF;
	 * soc_dq_odt = (tmp >> 8) & 0xFF;
	 *
	 * tmp = read_mc_reg(USER_DEF_REG_12_ADDR);
	 *
	 * dram_dq_drive = (tmp >> 0) & 0xFF;
	 * dram_dq_odt_wr1 = (tmp >> 8) & 0xFF;
	 * dram_dq_odt_wr2 = (tmp >> 16) & 0xFF;
	 * dram_dq_odt_rd2 = (tmp >> 24) & 0xFF;
	 */

	swap_phase = 1;

	read_lat = (dram == 2 ? 12 : 10) + (CEIL(RL, 2) * 2) - CEIL(WL, 2) + 28;
	trim_lat = (dram == 2 ? 11 : 9) + CEIL(RL, 2) - CEIL(WL, 2) + 29;

	/*
	 * Unused
	 * core_clk_margin_win_a = 15;
	 * core_clk_margin_win_b = 17;
	 * incr_winA_val = 9;
	 * incr_winB_val = 26;
	 */
	extra_addrctrl_dly = 26;
	ofs_dlls_trim_1 = -9;
	ofs_dlls_trim_3 = -10;

	// Step5
	tmp = ((WL == 5 ? 0x1 : 0x0) << 16) | 0x00100000;
	write_phy_reg(PHY_MODE0, tmp);

	// Step6
	write_phy_reg(DLLM_WINDOW_SIZE, 0x00000006);

	// Step7
	if (dram == 2) {
		// DDR4
		write_phy_reg(DDR4_CONFIG_1, 0x00000009);
	}

	// Step8
	write_phy_reg(UNIQUIFY_IO_3, (dram == 2 ? 1 : 0) << 27);
	write_phy_reg(UNIQUIFY_IO_2, (dram == 2 ? 1 : 0) << 24);

	// Step9
	tmp = ((dram == 0 ? 0 : 1) << 15) | ((dram_clk_period < 1000 ? 1 : 0) << 8) | 0x10004000;
	write_phy_reg(PHY_PAD_CTRL, tmp);

	// Step10
	write_phy_reg(PHY_PAD_CTRL_1,
		clk_drive | (clk_drive << 4) | (adrctrl_drive << 8) | (adrctrl_drive<<12) |
		(dq_dqs_drive << 16) | (dq_dqs_drive << 20));

	// Step11
	tmp = dq_dqs_term | ((dram == 2) ? 0 : (dq_dqs_term << 4));
	write_phy_reg(PHY_PAD_CTRL_2, tmp);

	// Step12
	write_phy_reg(PHY_PAD_CTRL_3, 0x00000000);

	// Step13
	for (i = 0; i < byte_lanes; i++) {
		write_phy_reg(PHY_LANE_SEL, 7 * i);
		write_phy_reg(VREF_TRAINING, (vref_value << 4) | 0x00000004);
	}

	// Step14
	write_phy_reg(VREF_CA_TRAINING, vref_ca_value);

	// Step15
	write_phy_reg(SCL_WINDOW_TRIM, 0x1A09002D);

	// Step16
	write_phy_reg(UNQ_ANALOG_DLL_1, 0x00000000);

	// Step17
	write_phy_reg(DYNAMIC_IE_TIMER, 0x0000001A);

	// Step18
	tmp = ((dram == 2 ? 0 : 1) << 2) | (CEIL(CL, 2) << 4) | (CEIL(AL, 2) << 8) |
			(odt_rd_map_cs0 << 16) | (odt_wr_map_cs0 << 24) | 0x00000001;
	write_phy_reg(SCL_CONFIG_1, tmp);

	// Step19
	tmp = (CEIL(CWL, 2) << 8) | ((((WL % 2) == 0) ? 0 : 1) << 24) | 0x80000001;
	write_phy_reg(SCL_CONFIG_2, tmp);

	// Step20
	write_phy_reg(SCL_CONFIG_3, sl_lanes ^ 0x3);

	// Step21
	write_phy_reg(DYNAMIC_WRITE_BIT_LVL, (trim_lat << 4) | (read_lat << 12));

	// Step22
	tmp = ((WL % 2) == 0) & swap_phase;
	write_phy_reg(SCL_CONFIG_4, tmp);

	// Step23
	write_phy_reg(SCL_GATE_TIMING, 0x00000170);

	// Step24
	write_phy_reg(WRLVL_DYN_ODT, mr2_wl | (mr2 << 16));

	// Step25
	write_phy_reg(WRLVL_ON_OFF, mr1 | (mr1_wl << 16));

	// Step26
	write_phy_reg(PHY_DLL_RECALIB, 0xAC001000);

	// Step27
	udelay(10);

	/*
	 * Step28 is skipped because dll_mas_dly is unused.
	 * dll_mas_dly = (*PHY_DLL_ADRCTRL>>24) & 0xFF;
	 */

	// Step29
	tmp = ((ofs_dlls_trim_3 < 0) ? 0 : sl_lanes);
	write_phy_reg(PHY_DLL_INCR_TRIM_3, tmp);

	// Step30
	tmp = ((ofs_dlls_trim_1 < 0) ? 0 : sl_lanes);
	write_phy_reg(PHY_DLL_INCR_TRIM_1, tmp);

	// Step31
	for (i = 0; i < byte_lanes; i++) {
		write_phy_reg(PHY_LANE_SEL, 6 * i);
		tmp = ((ofs_dlls_trim_1 < 0) ? -ofs_dlls_trim_1 : ofs_dlls_trim_1);
		write_phy_reg(PHY_DLL_TRIM_1, tmp);
		tmp = ((ofs_dlls_trim_3 < 0) ? -ofs_dlls_trim_3 : ofs_dlls_trim_3);
		write_phy_reg(PHY_DLL_TRIM_3, tmp);
	}

	// Step32
	write_phy_reg(PHY_DLL_ADRCTRL, ((extra_addrctrl_dly & 0x7F) << 0) | 0x00000200);

	// Step33
	write_phy_reg(PHY_LANE_SEL, 0);
	write_phy_reg(PHY_DLL_TRIM_CLK, (extra_addrctrl_dly << 0) | 0x00000080);

	// Step34
	write_phy_reg(PHY_DLL_RECALIB, ((extra_addrctrl_dly & 0x7F) << 0) | (0x10 << 8) | 0xAC000000);

	// Step35
	write_phy_reg(SCL_LATENCY, 0x00035076);

	// Step36
	write_phy_reg(BIT_LVL_CONFIG, 0x00000032);

	/* Step37 */
	lpddr4_combo_io_cal();

	// Step38
	rmw_phy_reg(PHY_DLL_RECALIB, 0xFBFFFFFF, 0x00000000);

	// Step39
	rmw_phy_reg(PHY_CTRL0, 0xFFFFF0FE, (sl_lanes << 8));
}

static void exec_trainingWRLVL(uint32_t sl_lanes)
{
	uint32_t tmp;

	// Step2
	tmp = read_phy_reg(DDRPHY_R24);
	write_phy_reg(DDRPHY_R24, tmp | 0x01000000);

	// Step3
	write_phy_reg(DDRPHY_R37, sl_lanes);

	// Step4
	write_phy_reg(DDRPHY_R31, 0x00010000);

	// Step5
	write_phy_reg(DDRPHY_R18, 0x50200000);

	// Step6
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step7 - Step8
	if (((read_phy_reg(DDRPHY_R36) & sl_lanes) != sl_lanes) ||
	   ((read_phy_reg(DDRPHY_R37) & sl_lanes) != 0)) {
		panic();
	}

	// Step9
	write_phy_reg(DDRPHY_R24, tmp);
}

static void exec_trainingVREF(uint32_t sl_lanes, uint32_t byte_lanes)
{
	uint32_t vref_mid_level_code;
	uint32_t vref_training_value;
	uint32_t sweep_range;
	uint16_t current_vref = 0;
	uint32_t best_window_diff_so_far[MAX_BYTE_LANES];
	uint32_t num_best_vref_matches[MAX_BYTE_LANES];
	uint32_t all_best_vref_matches[MAX_BYTE_LANES][MAX_BEST_VREF_SAVED];
	uint8_t window_0, window_1, window_diff;
	uint32_t highest_best_vref_val, lowest_best_vref_val;
	uint8_t orig_cs_config;
	uint32_t tmp;
	int i, j;

	// Step2
	for (i = 0; i < byte_lanes; i++) {
		write_phy_reg(DDRPHY_R29, i);
		rmw_phy_reg(DDRPHY_R07, 0xFFFFFFCF, 0x00000010);
	}
	// Step3
	vref_mid_level_code = (read_mc_reg(DDRMC_R040) >> 16) & 0xFF;
	sweep_range = read_mc_reg(DDRMC_R043) & 0xFF;

	// Step4
	for (i = 0; i < byte_lanes; i++) {
		best_window_diff_so_far[i] = 255;
		num_best_vref_matches[i] = 0;
	}

	// Step5
	for (vref_training_value = 0;
		 vref_training_value < (sweep_range * 2) + 1;
		 vref_training_value += VREF_SETP) {
		// Step5.1
		if (vref_training_value < sweep_range + 1) {
			if (vref_mid_level_code < vref_training_value + 2) {
				vref_training_value = sweep_range;
				continue;
			} else {
				current_vref = vref_mid_level_code - vref_training_value;
			}
		} else {
			if ((vref_mid_level_code + vref_training_value - sweep_range) > 126) {
				break;
			} else {
				current_vref = vref_mid_level_code + vref_training_value - sweep_range;
			}
		}
		for (i = 0; i < byte_lanes; i++) {
			write_phy_reg(DDRPHY_R29, 7 * i);
			write_phy_reg(DDRPHY_R66, (current_vref << 4) | 0x00000001);
		}

		// Step5.2
		write_phy_reg(DDRPHY_R18, 0x30800000);
		while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
			;

		// Step5.3
		for (i = 0; i < byte_lanes; i++) {
			if (((read_phy_reg(DDRPHY_R59) >> (14 + i)) & 0x1) == 0x0) {
				VERBOSE("BL2: PHY side VREF training passed on lane %0d, current_vref = %0d\n", i, current_vref);
				write_phy_reg(DDRPHY_R29, i * 6);
				window_0 = read_phy_reg(DDRPHY_R69) & 0x3F;
				window_1 = (read_phy_reg(DDRPHY_R69) >> 8) & 0x3F;
				window_diff = (window_0 > window_1) ?
								window_0 - window_1 : window_1 - window_0;
				VERBOSE("BL2: window_0 = %0d, window_1 = %0d, window_diff = %0d\n", window_0, window_1, window_diff);
				if (window_diff < best_window_diff_so_far[i]) {
					best_window_diff_so_far[i] = window_diff;
					all_best_vref_matches[i][0] = current_vref;
					num_best_vref_matches[i] = 1;
					VERBOSE("BL2: CURRENT BEST VREF PHY side :%d\n", current_vref);
				} else if ((window_diff == best_window_diff_so_far[i]) &&
						(num_best_vref_matches[i] < MAX_BEST_VREF_SAVED)) {
					all_best_vref_matches[i][num_best_vref_matches[i]] = current_vref;
					num_best_vref_matches[i] += 1;
				}
			} else {
				ERROR("BL2: PHY side VREF training failed lane %d, current_vref = %d\n",
					i, current_vref);
			}
		}
		// Step5.4
	}

	// Step6
	for (i = 0; i < byte_lanes; i++) {
		highest_best_vref_val = 0x0;
		lowest_best_vref_val = 0x7F;
		for (j = 0; j < num_best_vref_matches[i]; j++) {
			highest_best_vref_val =
				_MAX(all_best_vref_matches[i][j], highest_best_vref_val);
			lowest_best_vref_val  =
				_MIN(all_best_vref_matches[i][j], lowest_best_vref_val);
		}
		current_vref = (highest_best_vref_val + lowest_best_vref_val) >> 1;
		write_phy_reg(DDRPHY_R29, 7 * i);
		write_phy_reg(DDRPHY_R66, current_vref << 4);
	}

	// Step7
	write_phy_reg(DDRPHY_R19, 0xFF00FF00);
	write_phy_reg(DDRPHY_R20, 0xFF00FF00);

	// Step8
	write_phy_reg(DDRPHY_R18, 0x30800000);
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step9
	tmp = (read_phy_reg(DDRPHY_R59) >> 14) & sl_lanes;
	if ((tmp ^ sl_lanes) != sl_lanes) {
		panic();
	}

	// Step10
	rmw_phy_reg(DDRPHY_R54, 0xFFFFFF7F, 0x00000080);

	// Step11
	vref_mid_level_code = (read_mc_reg(DDRMC_R043) >> 8) & 0xFF;
	sweep_range = (read_mc_reg(DDRMC_R043) >> 16) & 0xFF;

	// Step12
	orig_cs_config = read_phy_reg(DDRPHY_R25) & 0x3;

	// Step13
	setup_vref_training_registers(vref_mid_level_code, sl_lanes, 1);

	// Step14
	rmw_phy_reg(DDRPHY_R66, 0xFFFFFFFE, 0x00000001);

	// Step15
	for (i = 0; i < byte_lanes; i++) {
		best_window_diff_so_far[i] = 255;
		num_best_vref_matches[i] = 0;
	}

	// Step16
	for (vref_training_value = 0;
		 vref_training_value < (sweep_range * 2) + 1;
		 vref_training_value += VREF_SETP) {
		// Step16.1
		if (vref_training_value < (sweep_range + 1)) {
			if (vref_training_value > vref_mid_level_code) {
				vref_training_value = sweep_range;
				continue;
			} else {
				current_vref = vref_mid_level_code - vref_training_value;
			}
		} else {
			if ((vref_mid_level_code + vref_training_value - sweep_range) <= 73) {
				current_vref =
					vref_mid_level_code + vref_training_value - sweep_range;
			} else {
				break;
			}
		}
		setup_vref_training_registers(current_vref, orig_cs_config, 0);

		// Step16.2
		write_phy_reg(DDRPHY_R18, 0x30500000);
		while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
			;

		// Step16.3
		tmp = (read_phy_reg(DDRPHY_R64) >> 20) & sl_lanes;
		for (i = 0; i < byte_lanes; i++) {
			if ((tmp ^ sl_lanes) == sl_lanes) {
				VERBOSE("BL2: VREF training passed during VrefDQ training DRAM side, current_vref = %d\n", current_vref);
				write_phy_reg(DDRPHY_R29, i * 6);
				window_0 = read_phy_reg(DDRPHY_R69) & 0x3F;
				window_1 = (read_phy_reg(DDRPHY_R69) >> 8) & 0x3F;
				window_diff = (window_0 > window_1) ?
								window_0 - window_1 : window_1 - window_0;
				VERBOSE("BL2: window_0 = %0d, window_1 = %0d, window_diff = %0d\n", window_0, window_1, window_diff);
				if (window_diff < best_window_diff_so_far[i]) {
					best_window_diff_so_far[i] = window_diff;
					all_best_vref_matches[i][0] = current_vref;
					num_best_vref_matches[i] = 1;
					VERBOSE("BL2: CURRENT BEST VREF DRAM side :%d\n", current_vref);
				} else if ((window_diff == best_window_diff_so_far[i]) &&
						(num_best_vref_matches[i] < MAX_BEST_VREF_SAVED)) {
					all_best_vref_matches[i][num_best_vref_matches[i]] = current_vref;
					num_best_vref_matches[i] += 1;
				}
			} else {
				ERROR("BL2: VREF training failed during VrefDQ training DRAM side, current_vref = %d\n", current_vref);
			}
		}
		// Step16.4
	}

	// Step17
	highest_best_vref_val = 0x0;
	lowest_best_vref_val = 0x7F;
	for (i = 0; i < byte_lanes; i++) {
		for (j = 0; j < num_best_vref_matches[i]; j++) {
			highest_best_vref_val =
				_MAX(all_best_vref_matches[i][j], highest_best_vref_val);
			lowest_best_vref_val  =
				_MIN(all_best_vref_matches[i][j], lowest_best_vref_val);
		}
	}
	current_vref = (highest_best_vref_val + lowest_best_vref_val) >> 1;

	// Step18
	setup_vref_training_registers(current_vref, sl_lanes, 0);

	// Step19
	rmw_mc_reg(DDRMC_R044, 0xFFFFFF00, current_vref);

	// Step20
	rmw_phy_reg(DDRPHY_R66, 0xFFFFFFFE, 0x00000000);

	// Step21
	setup_vref_training_registers(current_vref, sl_lanes, 2);

	// Step22
	rmw_phy_reg(DDRPHY_R54, 0xFFFFFF7F, 0x00000000);

	// Step23
	for (i = 0; i < byte_lanes; i++) {
		write_phy_reg(DDRPHY_R29, i);
		rmw_phy_reg(DDRPHY_R07, 0xFFFFFFCF, 0x00000030);
	}
}

static void setup_vref_training_registers(uint8_t vref_value, uint8_t cs, uint8_t turn_on_off_vref_training)
{
	uint8_t vref_op_code;
	uint16_t mr;

	// Step1
	if (vref_value > 50) {
		vref_op_code = vref_value - 23;
	} else {
		vref_op_code = vref_value | (1 << 6);
	}

	// Step2
	mr = read_mc_reg(DDRMC_R017) & 0xFF00;
	write_mr(cs, 6,
		mr | (((turn_on_off_vref_training == 2) ? 0 : 1) << 7) | vref_op_code);

	// Step3
	udelay(1);
}

static void write_mr(uint8_t cs, uint8_t mrw_sel, uint16_t mrw_data)
{
	uint8_t mrw_cs;
	uint8_t mrw_allcs;

	// Step1
	mrw_cs = 0;
	if (cs & 0x1) {
		rmw_mc_reg(DDRMC_R013, 0xFFFF0000, mrw_data);
		mrw_cs = 0;
	}
	if (cs & 0x2) {
		rmw_mc_reg(DDRMC_R014, 0xFFFF0000, mrw_data);
		mrw_cs = 1;
	}
	mrw_allcs = ((cs & 0x3) == 0x3) ? 1 : 0;

	// Step2
	rmw_mc_reg(DDRMC_R008, 0xFC000000,
		0x02800000 | (mrw_allcs << 24) | (mrw_cs << 8) | mrw_sel);

	// Step3
	while ((read_mc_reg(DDRMC_R022) & (1 << 3)) != (1 << 3))
		;

	// Step4
	rmw_mc_reg(DDRMC_R024, 0xFFFFFFF7, 0x00000008);
}

static void exec_trainingBITLVL(uint32_t sl_lanes)
{
	uint32_t tmp;

	// Step2
	write_phy_reg(DDRPHY_R62, 0x00000000);

	// Step3
	write_phy_reg(DDRPHY_R19, 0xFF00FF00);
	write_phy_reg(DDRPHY_R20, 0xFF00FF00);

	// Step4
	write_phy_reg(DDRPHY_R18, 0x30A00000);

	// Step5
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step6
	tmp = (read_phy_reg(DDRPHY_R59) >> 14) & sl_lanes;
	if ((tmp ^ sl_lanes) != sl_lanes) {
		panic();
	}

	// Step7
	rmw_phy_reg(DDRPHY_R54, 0xFFFFFF7F, 0x00000080);

	// Step8
	write_phy_reg(DDRPHY_R18, 0x30700000);

	// Step9
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step10
	tmp = (read_phy_reg(DDRPHY_R64) >> 20) & sl_lanes;
	if ((tmp ^ sl_lanes) != sl_lanes) {
		panic();
	}

	// Step11
	rmw_phy_reg(DDRPHY_R54, 0xFFFFFF7F, 0x00000000);

	// Step12
	write_phy_reg(DDRPHY_R51, 0x00080000);

	// Step13
	write_phy_reg(DDRPHY_R18, 0x11200000);

	// Step14
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step15
	write_phy_reg(DDRPHY_R51, 0x00000000);

	// Step16
	write_phy_reg(DDRPHY_R18, 0x30A00000);

	// Step17
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;
}

static void opt_delay(uint32_t sl_lanes, uint32_t byte_lanes)
{
	uint16_t dlls_trim_ca;
	uint16_t dlls_trim_2[MAX_BYTE_LANES];
	uint16_t op_dqs_trim[MAX_BYTE_LANES];
	uint16_t min_WL = 128;
	uint16_t min_WD = 128;
	uint32_t val;
	int lane, bit_sel;

	/* Step 2 */
	rmw_phy_reg(PHY_DLL_RECALIB, 0xFBFFFFFF, 0x04000000);

	/* Step 3 */
	rmw_mc_reg(LP_CMD_ADDR, ~(0x7F << LP_CMD_OFFSET), (0x00000011 << LP_CMD_OFFSET));

	while (read_mc_field(LP_STATE_ADDR, LP_STATE_WIDTH, LP_STATE_OFFSET) != 0x48)
		;

	/* Step 4 */
	write_phy_reg(PHY_LANE_SEL, 0 * 8);
	dlls_trim_ca = (read_phy_reg(PHY_DLL_TRIM_CLK) >> 0) & 0x7F;
	min_WL = dlls_trim_ca;
	for (lane = 0; lane < byte_lanes; lane++) {
		write_phy_reg(PHY_LANE_SEL, 6 * lane);
		dlls_trim_2[lane] = (read_phy_reg(PHY_DLL_TRIM_2) >> 0) & 0x3F;
		if (dlls_trim_2[lane] < min_WL) {
			min_WL = dlls_trim_2[lane];
		}

		write_phy_reg(PHY_LANE_SEL, (lane * 7) | 0x00000900);
		op_dqs_trim[lane] = (read_phy_reg(OP_DQ_DM_DQS_BITWISE_TRIM) >> 0) & 0x3F;
		if (op_dqs_trim[lane] < min_WD) {
			min_WD = op_dqs_trim[lane];
		}

		for (bit_sel = 0; bit_sel < 9; bit_sel++) {
			write_phy_reg(PHY_LANE_SEL, (lane * 7) | (bit_sel << 8));
			val = (read_phy_reg(OP_DQ_DM_DQS_BITWISE_TRIM) >> 0) & 0x7F;
			val = (val & 0x40) ? (op_dqs_trim[lane] + (val & 0x3F)) : (op_dqs_trim[lane] - (val & 0x3F));
			if (val < min_WD) {
				min_WD = val;
			}
		}
	}

	/* Step 5 */
	val = (dlls_trim_ca - min_WL) & 0x7F;
	write_phy_reg(PHY_LANE_SEL, 0 * 8);
	write_phy_reg(PHY_DLL_TRIM_CLK, (val << 0) | 0x00000080);
	write_phy_reg(PHY_DLL_ADRCTRL, (val << 0) | 0x00000200);
	rmw_phy_reg(PHY_DLL_RECALIB, 0xFFFFFF80, (val << 0));

	for (lane = 0; lane < byte_lanes; lane++) {
		val = (dlls_trim_2[lane] - min_WL) & 0x3F;
		write_phy_reg(PHY_LANE_SEL, 6 * lane);
		rmw_phy_reg(PHY_DLL_TRIM_2, 0xFFFFFFC0, (val << 0));
		write_phy_reg(PHY_LANE_SEL, (lane * 7) | 0x00000900);
		val = (op_dqs_trim[lane] - min_WD) & 0x3F;
		rmw_phy_reg(OP_DQ_DM_DQS_BITWISE_TRIM, 0xFFFFFF80, (val << 0));
	}

	/* Step 6 */
	rmw_mc_set_field(LPC_SR_ZQ_EN_ADDR, LPC_SR_ZQ_EN_WIDTH, LPC_SR_ZQ_EN_OFFSET, 0x00000000);
	rmw_mc_set_field(LP_CMD_ADDR, LP_CMD_WIDTH, LP_CMD_OFFSET, 0x00000002);

	while (read_mc_field(LP_STATE_ADDR, LP_STATE_WIDTH, LP_STATE_OFFSET) != 0x40)
		;

	udelay(1);
	rmw_mc_set_field(LPC_SR_ZQ_EN_ADDR, LPC_SR_ZQ_EN_WIDTH, LPC_SR_ZQ_EN_OFFSET, 0x00000001);

	/* Step 7 */
	rmw_mc_set_field(INT_ACK_LOWPOWER_ADDR, INT_ACK_LOWPOWER_WIDTH, INT_ACK_LOWPOWER_OFFSET, 0x0009);

	while (read_mc_field(INT_STATUS_LOWPOWER_ADDR, INT_STATUS_LOWPOWER_WIDTH, INT_STATUS_LOWPOWER_OFFSET) != 0x0000)
		;

	/* Step 8 */
	rmw_phy_reg(PHY_DLL_RECALIB, 0xFBFFFFFF, 0x00000000);
	while ((read_phy_reg(UNQ_ANALOG_DLL_2) & 0x3) != sl_lanes)
		;
}

static void exec_trainingSL(uint32_t sl_lanes)
{
	// Step2
	write_phy_reg(DDRPHY_R62, 0x00000001);

	// Step3
	write_phy_reg(DDRPHY_R34, 0x00000010);

	// Step4
	write_phy_reg(DDRPHY_R19, 0x789B3DE0);
	write_phy_reg(DDRPHY_R20, 0xF10E4A56);

	// Step5
	write_phy_reg(DDRPHY_R18, 0x11200000);

	// Step6
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step7
	write_phy_reg(DDRPHY_R18, 0x11200000);

	// Step8
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step9
	write_phy_reg(DDRPHY_R18, 0x34200000);

	// Step10
	while ((read_phy_reg(DDRPHY_R18) & 0x10000000) != 0x00000000)
		;

	// Step11
	if ((read_phy_reg(DDRPHY_R18) & sl_lanes) != sl_lanes) {
		panic();
	}

	// Step12
	write_phy_reg(DDRPHY_R62, 0x00000003);
}

static void program_phy2(void)
{
	uint16_t dram_clk_period;
	uint32_t tmp, b21, b22, b23;

	// Step1
	tmp = read_mc_reg(DDRMC_R039);
	dram_clk_period = tmp & 0xFFFF;
	b21 = (tmp >> 21) & 0x1;
	b22 = (tmp >> 22) & 0x1;
	b23 = (tmp >> 23) & 0x1;

	// Step2
	rmw_phy_reg(DDRPHY_R64, 0xFFFFFFFE, b23);
	rmw_phy_reg(DDRPHY_R59, 0xFFFFFFFE, (b23 == 1 ? 0 : b22));
	write_phy_reg(DDRPHY_R55, (b21 << 24) |
		_MIN(1000000000000 / (2 * dram_clk_period * 256), 0xFFFFFF));

	// Step3
	rmw_phy_reg(DDRPHY_R27, 0xFBFFFFFF, 0x04000000);
	rmw_phy_reg(DDRPHY_R27, 0xFC0000FF,
		_MIN(1000000000000 / (dram_clk_period * 256), 0x3FFFF) << 8);
	rmw_phy_reg(DDRPHY_R27, 0xFBFFFFFF, 0x00000000);
}

static void program_mc2(void)
{
	uint8_t main_clk_dly;
	uint8_t tphy_rdlat;
	uint32_t tmp;

	// Step1
	main_clk_dly = (read_phy_reg(DDRPHY_R21) >> 4) & 0xF;
	tmp = (read_mc_reg(DDRMC_R028) >> 24) & 0x7F;
	tphy_rdlat = ((main_clk_dly + 1 + 1) * 2) + 2 + ((tmp == 1) ? 2 : 0);

	// Step2
	rmw_mc_reg(DDRMC_R027, 0xFFFFFF80, tphy_rdlat & 0x7F);
}


void ddr_eye_open_tool(open_eye_memory_t *mem, dmac_setting_t *dmac)
{
	uint32_t	reg;
	uint32_t	rank;
	uint32_t	lane;
	uint32_t	bit_sel;
	uint8_t		vref_code_write;
	uint8_t		vref_value_read;
	uint8_t		vref_code_read;
	int8_t		current_vref;
	int			dly_code;
	int8_t		dly;
	int			i, j;
	static uint16_t compareResult[RANK_NUM][DLY_LEN] = {0};

	rmw_phy_reg(DDRPHY_R27, 0xFBFFFFFF, 0x04000000);
	rmw_phy_reg(DDRPHY_R55, 0xFEFFFFFF, 0x00000000);
	while(1)
	{
		reg = read_phy_reg(DDRPHY_R18);
		if((reg & 0x10000000) == 0x00000000){
			break;
		}
	}

	// 3) Get configurations.
	reg = read_mc_reg(DDRMC_R019);
	reg = (reg >> 0) & 0x01;
	if(reg == 0){
		setting.scl_lanes = 3;
		setting.byte_lanes = 2;
	}else{
		setting.scl_lanes = 1;
		setting.byte_lanes = 1;
	}

	setting.cs_bit = 34 - 1 - reg;
	reg = read_mc_reg(DENALI_CTL_122);
	setting.cs_bit -= ((reg >> 24) & 0x07);
	reg = read_mc_reg(DENALI_CTL_123);
	setting.cs_bit -= ((reg >> 8) & 0x0F);
	reg = read_mc_reg(DENALI_CTL_122);
	setting.cs_bit -= ((reg >> 8) & 0x03);

	reg = read_mc_reg(DDRMC_R039);
	setting.dram_clk_period = reg & 0xFFFF;
	setting.dram = (reg >> 16) & 0x0F;

	reg = read_mc_reg(DENALI_CTL_132);
	if(((reg >> 16) & 0x03) == 0x03){
		setting.ranks = 2;
	}else{
		setting.ranks = 1;
	}

	for (rank = 0; rank < setting.ranks; rank++){
		setting.addr[rank] = RZG2L_DDR1_BASE + 0x1000 + (rank << setting.cs_bit);
	}

	// 4) Set range.
	setting.vref_code_write_min = 0;			// 45.00%
	if(setting.dram == 2){
		setting.vref_code_write_max = 73;		// 92.50%
	}else{
		setting.vref_code_write_max = setting.vref_code_write_min;
	}
	setting.vref_code_write_step = 1;
	setting.vref_code_read_min = 2;				// 10.00%
	setting.vref_code_read_max = 126;			// 90.96%
	setting.vref_code_read_step = 1;
	setting.dly_code_min = -31;					// -11.78%
	setting.dly_code_max = 32;					// 29.80%
	setting.dly_code_step = -1;

	// 5) Get the DLL calibration result.
	reg = read_phy_reg(DDRPHY_R28);
	setting.dll_mas_dly = (reg >> 24) & 0xFF;
	setting.step_dly = setting.dram_clk_period / setting.dll_mas_dly;	// 1 step delay [ps]

	// 6) Get default values
	lane = 0;
	reg = lane * 7;
	write_phy_reg(DDRPHY_R29, reg);
	reg = read_phy_reg(DDRPHY_R66);
	vref_value_read = (reg >> 4) & 0x7F;
	if(vref_value_read == 127){
		vref_code_read = 63;
	}else{
		vref_code_read = vref_value_read;
	}

	if(setting.dram == 2){
		reg = read_mc_reg(DDRMC_R044);
		vref_code_write = reg & 0xFF;
	}else{
		vref_code_write = 0;
	}

	for(lane = 0; lane < setting.byte_lanes; lane++)
	{
		for(bit_sel = 0; bit_sel < 9; bit_sel++)
		{
			reg = (bit_sel << 8) | (lane * 7);
			write_phy_reg(DDRPHY_R29, reg);

			reg = read_phy_reg(DDRPHY_R56);
			setting.op_dq_trim[lane][bit_sel] = reg & 0x3F;
			if ((reg & 0x40) == 0){
				setting.op_dq_trim[lane][bit_sel] *= -1;
			}

			if(bit_sel < 8){
				reg = read_phy_reg(DDRPHY_R54);
				setting.ip_dq_trim[lane][bit_sel] = reg & 0x3F;
				if ((reg & 0x40) == 0){
					setting.ip_dq_trim[lane][bit_sel] *= -1;
				}
			}
		}
	}

	// 7) Output default values

	// 8) Measure the write eye
	if(setting.dram == 2){
		setup_vref_training_registers(vref_code_write, setting.scl_lanes, 1);
	}

	PutStr("",1);
	PutStr("[Write]",0);
	PutStr("",1);
	PutStr("1                                                            100",1);

	current_vref = vref_code_write;	//fix vref to write leveling value

	for(dly_code = setting.dly_code_max; dly_code >= setting.dly_code_min; dly_code += setting.dly_code_step)
	{
		// Write the inversion data
		if(setting.dram == 2){
			setup_vref_training_registers(vref_code_write, setting.scl_lanes, 0);
		}
		for(lane = 0; lane < setting.byte_lanes; lane++){
			for(bit_sel = 0; bit_sel < 9; bit_sel++){
				reg = (bit_sel << 8) | (lane * 7);
				write_phy_reg(DDRPHY_R29, reg);
				write_phy_reg(DDRPHY_R56, 0x00000000);
			}
		}
		dram_write(&setting.addr[0], setting.ranks, (uint64_t *)mem->p_wr_pattern_inv, mem->pattern_bytes, dmac);

		// Write and Read
		if(setting.dram == 2){
			setup_vref_training_registers(current_vref, setting.scl_lanes, 0);
		}
		for(lane = 0; lane < setting.byte_lanes; lane++){
			for(bit_sel = 0; bit_sel < 9; bit_sel++){
				reg = (bit_sel << 8) | (lane * 7);
				write_phy_reg(DDRPHY_R29, reg);

				dly = setting.op_dq_trim[lane][bit_sel] + dly_code;
				if(dly < -63){
					dly = -63;
				}else if(dly > 63){
					dly = 63;
				}

				if(dly < 0){
					reg = dly * -1;
				}else{
					reg = dly + 0x40;
				}
				write_phy_reg(DDRPHY_R56, 0x00000180 | reg);
			}
		}
		dram_write(&setting.addr[0], setting.ranks, (uint64_t *)mem->p_wr_pattern, mem->pattern_bytes, dmac);
		dram_read(&setting.addr[0], setting.ranks, mem->p_rd_buf, (uint32_t *)mem->p_wr_pattern, mem->pattern_bytes, dmac,\
			compareResult, (DLY_CODE_MAX - dly_code));
	}
	PutStr("",1);
	PutStr("",1);

	drawResult(setting.ranks, compareResult);

	// 9) Reset vref_code_write and op_dq_trim
	if(setting.dram == 2){
		setup_vref_training_registers(vref_code_write, setting.scl_lanes, 0);
	}

	for(lane = 0; lane < setting.byte_lanes; lane++){
		for(bit_sel = 0; bit_sel < 9; bit_sel++){
			reg = (bit_sel << 8) | (lane * 7);
			write_phy_reg(DDRPHY_R29, reg);
			write_phy_reg(DDRPHY_R56, 0x00000000);
		}
	}

	// 10) Prepare to measure the read eye
	dram_write(&setting.addr[0], setting.ranks, (uint64_t *)mem->p_wr_pattern, mem->pattern_bytes, dmac);

	// 11) Measure the read eye
	PutStr("",1);
	PutStr("[Read]",0);
	PutStr("",1);
	PutStr("1                                                            100",1);

	current_vref = vref_code_read;

	for(dly_code = setting.dly_code_max; dly_code >= setting.dly_code_min; dly_code += setting.dly_code_step){
		//Read
		for(lane = 0; lane < setting.byte_lanes; lane++){
			reg = lane * 7;
			write_phy_reg(DDRPHY_R29, reg);
			reg = ((current_vref << 4) | 0x00000001);
			write_phy_reg(DDRPHY_R66, reg);

			for(bit_sel = 0; bit_sel < 8; bit_sel++){
				reg = (bit_sel << 8) | (lane * 7);
				write_phy_reg(DDRPHY_R29, reg);

				dly = setting.ip_dq_trim[lane][bit_sel] + dly_code;
				if(dly < -63){
					dly = -63;
				}else if(dly > 63){
					dly = 63;
				}

				if(dly < 0){
					reg = dly * -1;
				}else{
					reg = dly + 0x40;
				}
				write_phy_reg(DDRPHY_R54, 0x00000080 | reg);
			}
		}
		dram_read(&setting.addr[0], setting.ranks, mem->p_rd_buf, (uint32_t *)mem->p_wr_pattern, mem->pattern_bytes, dmac,\
			compareResult, (DLY_CODE_MAX - dly_code));
	}

	PutStr("",1);
	PutStr("",1);

	drawResult(setting.ranks, compareResult);


	// 12) Reset vref_code_read and ip_dq_trim
	for(lane = 0; lane < setting.byte_lanes; lane++){
		reg = lane * 7;
		write_phy_reg(DDRPHY_R29, reg);
		reg = ((vref_value_read << 4) | 0x00000000);
		write_phy_reg(DDRPHY_R66, reg);

		for(bit_sel = 0; bit_sel < 8; bit_sel++){
			reg = (bit_sel << 8) | (lane * 7);
			write_phy_reg(DDRPHY_R29, reg);
			write_phy_reg(DDRPHY_R54, 0x00000000);
		}
	}
	PutStr("FINISH!",1);
}

static void dram_write(uint64_t *addr, uint8_t rank_num,
						uint64_t *wr_data, uint32_t bytes, dmac_setting_t *dmac)
{
	dmac_errcode_t dmac_err;
	uint32_t rank;

	for (rank = 0; rank < rank_num; rank++){
		dmac->src_addr = (uint64_t)wr_data;
		dmac->dst_addr = addr[rank];
		dmac->transfer_byte = bytes;
		dmac->non_secure_flag = 0;
		dmac->rsel = 0;
		dmac_err = dmac_transfer_single(dmac);

		if(dmac_err != DMAC_ERRCODE_SUCCESS){
			PutStr("",1);
			PutStr("!!! DMAC Error !!!",1);
			while(1);
		}
	}
	return;
}

static void dram_read(uint64_t *addr, uint8_t rank_num,
						uint32_t *rd_buf, uint32_t *exp_data, uint32_t bytes, dmac_setting_t *dmac,
						uint16_t compareResult[][DLY_LEN], uint16_t dly)
{
	dmac_errcode_t dmac_err;
	uint32_t tmp;
	uint8_t rank;
	uint8_t dq_bit;
	uint16_t i, j;

	for(i = 0; i < (bytes / sizeof(uint32_t)); i++){
		rd_buf[i] = 0;
	}

	PutStr("#",0);

	for(rank = 0; rank < rank_num; rank++){
		dmac->src_addr = addr[rank];
		dmac->dst_addr = (uint64_t)rd_buf;
		dmac->transfer_byte = bytes;
		dmac->non_secure_flag = 0;
		dmac->rsel = 0;
		dmac_err = dmac_transfer_single(dmac);
		if(dmac_err != DMAC_ERRCODE_SUCCESS){
			PutStr("",1);
			PutStr("!!! DMAC Error !!!",1);
			while(1);
		}

		// Compare
		for(i = 0; i < (bytes / sizeof(uint32_t)); i++){
			tmp = rd_buf[i] ^ exp_data[i];

			for(j = 0; j < 32; j++){
				dq_bit = j % 16;
				if (((tmp >> j) & 0x1) != 0){
					compareResult[rank][dly] |= (1 << dq_bit);
				}
			}
		}
	}
}

static void drawResult(const uint8_t rank_num, const uint16_t compareResult[][DLY_LEN]){
	int rank, dq_bit, dly;
	const char *rank_str[] = { "RANK[0]", "RANK[1]" };
	const char *dq_str[] = {"DQ[00]:\t", "DQ[01]:\t", "DQ[02]:\t", "DQ[03]:\t", \
							"DQ[04]:\t", "DQ[05]:\t", "DQ[06]:\t", "DQ[07]:\t", \
							"DQ[08]:\t", "DQ[09]:\t", "DQ[10]:\t", "DQ[11]:\t", \
							"DQ[12]:\t", "DQ[13]:\t", "DQ[14]:\t", "DQ[15]:\t" };

	for (rank = 0; rank < rank_num; rank++){
		PutStr(rank_str[rank],1);
		PutStr("DQ# vs Delay (-31 to 32 [tap])",1);

		for (dq_bit = 0; dq_bit < DQ_NUM; dq_bit++){
			PutStr(dq_str[dq_bit],0);

			for (dly = 0; dly < DLY_LEN; dly++){
				if ( (dly == (DLY_LEN - DLY_CODE_MAX)) | (dly == (DLY_LEN - DLY_CODE_MAX - 1)) ) {	//center dly
					PutStr("|",0);
				}else if(((compareResult[rank][dly] >> dq_bit) & 1) == 0){
					PutStr(".",0);
				}else{
					PutStr("X",0);
				}
			}
			PutStr("",1);
		}
		PutStr("",1);
	}
}


static const uint32_t random_pattern[128] =
    {
        0x904870F2,0xD91DF163,0x1507433C,0x30FB119C,
		0xC2975CEF,0x91F22C84,0xD56FC7F0,0x761AC0E4,
		0x690394A5,0x08E56F70,0xB0C6D20B,0xBFA0592C,
		0x399C36D8,0xEB364AA8,0xC5021BFD,0x1F512C6B,
		0x6206890D,0x3E34A2E7,0x820906D7,0x9A4EB8D8,
		0xC4609E14,0xC5CAD47C,0x530EA50C,0xE612F119,
		0x615BEFD9,0xB0AFB28D,0x113C4CF1,0x9AF7DB34,
		0x8761F422,0x89D54C49,0x4193552B,0xA3128C49,
		0x9BE840C1,0x2DD43465,0x5AE1CA85,0xCC015BD4,
		0xD9F80733,0x81DCD1B1,0xD477F066,0x62032AD2,
		0x51F74AE0,0x78B0DC5E,0xFC0D8826,0x72A1BD53,
		0x4D6071DE,0x4F00CEEE,0x17DBD452,0xA692D308,
		0x5CF7418A,0x150BA864,0x38A4D2CC,0xA69BCB9A,
		0x6EFD5CC0,0x18D3AB5C,0xFD612C2E,0x7B871A19,
		0x664807AA,0x5A98E081,0xB44B9F79,0xD9465B68,
		0xAADF9BB0,0x4D047215,0x9B03FD24,0x70C187A4,
		0x8AE3C3F7,0x76C3C26D,0xE50C16C5,0xF14FFCC3,
		0x4FB69C74,0x39753FCC,0x71C666B2,0x1DFABC44,
		0x9E3E3839,0x7B70FEC9,0x086E1B93,0x58A2CD24,
		0xE9AFB0D5,0x89142B89,0xC5FFDDE2,0x12E0D116,
		0xA7453749,0x4AA2472D,0xC44E6B61,0xCDB580F2,
		0xC6346EBC,0x7A161B72,0x9652AE20,0x251A4C77,
		0x4FD73D90,0x908E4DA6,0x17B44C22,0xC9F770A0,
		0xE29B3F51,0xD6825D27,0x997CB544,0xAA3242D3,
		0x0652ED9B,0x3B6EF5FA,0xF54271FF,0x158DECB3,
		0xE06CD1AA,0x9EABE528,0xB488FD63,0x3F4D808F,
		0x77CAB801,0x8581AF23,0x63A9BCF6,0x914A4225,
		0x5570A01B,0x48870D95,0xED775086,0x82B02E24,
		0xFC6A2920,0x564A0C74,0xEF20B30E,0x9845E11B,
		0xC251D310,0x0E4CC150,0x311FF73A,0xCF1C0EBC,
		0xF3C1EA17,0xD03BF0B4,0xA3FF6246,0x4583E652,
		0x82A07184,0x74D6059F,0x171B2AF4,0xEFB67BF6
    };

int  ddr_test_auto_cmp( )
{
	
	volatile uint64_t addr;
	uint32_t	i;
	
	uint32_t	size = 20;
	uint32_t    data_num;
	uint32_t	read_data;
	char log_out_buf[200];
		
	addr = DDR_ACCESS_START_ADDR;
	data_num = 0;

	//Write
	for ( i=0; i<size; i++ ) {
		
		*(uint32_t *)addr = random_pattern[data_num];
		addr+=4;		
		data_num++;		
	}

	addr = DDR_ACCESS_START_ADDR;
	data_num = 0;

	//ReadCompare
	for ( i=0; i<size; i++ ) {
		
		read_data = *(uint32_t *)addr;
		addr+=4;	

		if (read_data != random_pattern[data_num] ){
			return 1;
			 
		}
		data_num++;		
	}
	return 0;

} /* end of func ddr_test_auto_cmp */

int scl_gate_timing_count_up(unsigned int sign_bit,unsigned int read_val ){
	unsigned int add_read_val;

	if ((sign_bit) == 0) {
			
		if(read_val == 0){
			add_read_val      = 0x00000012;
		}else{
			add_read_val      = read_val - 16;
		}
			
	}else {
			add_read_val      = read_val + 16;
	}
	return add_read_val;
} /* END OF FUNC scl_gate_timing_count_up */
