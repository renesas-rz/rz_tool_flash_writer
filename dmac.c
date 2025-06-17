#include "common.h"
#include "rzg2l_def.h"
#include "mmio.h"
#include "dmac_reg.h"
#include "dmac.h"
#include "cpg_regs.h"
#include "mmio.h"
#include "cpudrv.h"



static void sysc_write_reg(uint32_t offset, uint32_t val);
static uint32_t sysc_read_reg(uint32_t offset);
static void dmac_write_reg(uint64_t base, uint32_t offset, uint32_t val);
static uint32_t dmac_read_reg(uint64_t base, uint32_t offset);

static void sysc_write_reg(uint32_t offset, volatile uint32_t val)
{
	mmio_write_32(RZG2L_SYSC_BASE + offset, val);

	return;
}
static uint32_t sysc_read_reg(uint32_t offset)
{
	return mmio_read_32(RZG2L_SYSC_BASE + offset);

}

static void dmac_write_reg(uint64_t base, uint32_t offset, uint32_t val)
{
	*((volatile uint32_t *)(base + offset)) = val;
	return;
}

static uint32_t dmac_read_reg(uint64_t base, uint32_t offset)
{
	uint32_t val;
	val = *((volatile uint32_t *)(base + offset));
	return val;
}


void dmac_init(dmac_setting_t *setting)
{
	if(setting->non_secure_flag == 1)
	{
		setting->axi_base = RZG2L_DMAC_NS_AXI_BASE;
	}
	else
	{
		setting->axi_base = RZG2L_DMAC_S_AXI_BASE;
	}

	if(setting->ch <= 7)
	{
		setting->axi_base += (0x40 * setting->ch);
	}
	else
	{
		setting->axi_base += (0x400 + (0x40 * (setting->ch - 8)));
	}

	mmio_write_32(CPG_CLKON_DAMC_REG, 0x00030003);
	mmio_write_32(CPG_RST_DMAC, 0x00030003);
	udelay(1);

	return;
}


static void dmac_set_src_addr(dmac_setting_t *setting)
{
	const uint16_t sa_reg_offset[2] = {DMAC_N0SA, DMAC_N1SA};
	uint32_t reg;
	uint32_t addr_bit33_bit30;
	uint32_t addr_bit29_bit0;
	uint8_t shift_num;

	addr_bit33_bit30 = (setting->src_addr >> 30) & 0x0F;
	addr_bit29_bit0 = setting->src_addr & 0x3FFFFFFF;

	shift_num = 16 * setting->non_secure_flag;		/* Upper 16bit or Lower 16bit */
	shift_num += ((setting->ch & 0x01) * 4);		/* Even ch -> OFS00, Odd ch -> OFS01 */

	reg = sysc_read_reg(SYS_AOF6);
	reg &= ~(0xF << shift_num);
	reg |= (addr_bit33_bit30 << shift_num);
	sysc_write_reg(SYS_AOF6, reg);

	reg = ((setting->ch & 0x01) << 30) | addr_bit29_bit0;
	dmac_write_reg(setting->axi_base, sa_reg_offset[setting->rsel], reg);

	return;
}


static void dmac_set_dst_addr(dmac_setting_t *setting)
{
	const uint16_t da_reg_offset[2] = {DMAC_N0DA, DMAC_N1DA};
	uint32_t reg;
	uint32_t addr_bit33_bit30;
	uint32_t addr_bit29_bit0;
	uint8_t shift_num;

	addr_bit33_bit30 = (setting->dst_addr >> 30) & 0x0F;
	addr_bit29_bit0 = setting->dst_addr & 0x3FFFFFFF;

	shift_num = 16 * setting->non_secure_flag;		/* Upper 16bit or Lower 16bit */
	shift_num += (8 + ((setting->ch & 0x01) * 4));	/* Even ch -> OFS10, Odd ch -> OFS11 */

	reg = sysc_read_reg(SYS_AOF6);
	reg &= ~(0xF << shift_num);
	reg |= (addr_bit33_bit30 << shift_num);
	sysc_write_reg(SYS_AOF6, reg);

	reg = (1 << 31) | ((setting->ch & 0x01) << 30) | addr_bit29_bit0;
	dmac_write_reg(setting->axi_base, da_reg_offset[setting->rsel], reg);

	return;
}


dmac_errcode_t dmac_transfer_endless(dmac_setting_t *setting)
{
	const uint16_t tb_reg_offset[2] = {DMAC_N0TB, DMAC_N1TB};
	dmac_errcode_t err_code;
	uint32_t reg;

	while(1)
	{
		reg = dmac_read_reg(setting->axi_base, DMAC_CHSTAT);
		if((reg & (DMAC_CHSTAT_TACT | DMAC_CHSTAT_EN)) == 0)	/* Refer Transfer Flow */
		{
			break;
		}
	}

	reg = dmac_read_reg(setting->axi_base, DMAC_CHCTRL);
	reg |= DMAC_CHCTRL_SWRST;
	dmac_write_reg(setting->axi_base, DMAC_CHCTRL, reg);

	reg = dmac_read_reg(setting->axi_base, DMAC_CHCFG);
	reg &= ~(DMAC_CHCFG_DMS | DMAC_CHCFG_RSEL | DMAC_CHCFG_DEM | DMAC_CHCFG_RSW |
			DMAC_CHCFG_DAD | DMAC_CHCFG_SAD | DMAC_CHCFG_DDS | DMAC_CHCFG_SDS |
			DMAC_CHCFG_AM | DMAC_CHCFG_LVL | DMAC_CHCFG_HIEN | DMAC_CHCFG_LOEN |
			DMAC_CHCFG_REQD | DMAC_CHCFG_SEL);
	reg |= (DMAC_CHCFG_REN |		/* After a DMA transaction is completed, DMA transfers are continued using the Next register. */
			DMAC_CHCFG_TM | (7 << DMAC_CHCFG_DDS_SHIFT) | (7 << DMAC_CHCFG_SDS_SHIFT) |
			(4 << DMAC_CHCFG_AM_SHIFT) |		/* Block Transfer Mode */
			((setting->ch & 0x07) << DMAC_CHCFG_SEL_SHIFT));
	if(setting->rsel == 1)
	{
		reg |= DMAC_CHCFG_RSEL;
	}
	dmac_write_reg(setting->axi_base, DMAC_CHCFG, reg);

	dmac_set_src_addr(setting);
	dmac_set_dst_addr(setting);
	setting->transfer_byte &= 0x3FFFFFFF;			/* Max. 1GByte */
	dmac_write_reg(setting->axi_base, tb_reg_offset[setting->rsel], setting->transfer_byte);

	dmac_write_reg(setting->axi_base, DMAC_CHITVL, 0);

	reg = dmac_read_reg(setting->axi_base, DMAC_CHCTRL);
	reg |= DMAC_CHCTRL_SETEN;
	dmac_write_reg(setting->axi_base, DMAC_CHCTRL, reg);

	/* Set Software Trigger */
	reg = dmac_read_reg(setting->axi_base, DMAC_CHCTRL);
	reg |= DMAC_CHCTRL_STG;
	dmac_write_reg(setting->axi_base, DMAC_CHCTRL, reg);

	while(1)
	{
		reg = dmac_read_reg(setting->axi_base, DMAC_CHSTAT);
		if((reg & DMAC_CHSTAT_ER) == DMAC_CHSTAT_ER)
		{
			err_code = DMAC_ERRCODE_ERROR;
			break;
		}

		reg = dmac_read_reg(setting->axi_base, DMAC_CHCFG);
		reg |= DMAC_CHCFG_REN;
		dmac_write_reg(setting->axi_base, DMAC_CHCFG, reg);
	}

	return err_code;
}


dmac_errcode_t dmac_transfer_single(dmac_setting_t *setting)
{
	const uint16_t tb_reg_offset[2] = {DMAC_N0TB, DMAC_N1TB};
	dmac_errcode_t err_code;
	uint32_t reg;

	while(1)
	{
		reg = dmac_read_reg(setting->axi_base, DMAC_CHSTAT);
		if((reg & (DMAC_CHSTAT_TACT | DMAC_CHSTAT_EN)) == 0)	/* Refer Transfer Flow */
		{
			break;
		}
	}

	reg = dmac_read_reg(setting->axi_base, DMAC_CHCTRL);
	reg |= DMAC_CHCTRL_SWRST;
	dmac_write_reg(setting->axi_base, DMAC_CHCTRL, reg);

	reg = dmac_read_reg(setting->axi_base, DMAC_CHCFG);
	reg &= ~(DMAC_CHCFG_DMS | DMAC_CHCFG_RSEL | DMAC_CHCFG_DEM | DMAC_CHCFG_RSW |
			DMAC_CHCFG_DAD | DMAC_CHCFG_SAD | DMAC_CHCFG_DDS | DMAC_CHCFG_SDS |
			DMAC_CHCFG_AM | DMAC_CHCFG_LVL | DMAC_CHCFG_HIEN | DMAC_CHCFG_LOEN |
			DMAC_CHCFG_REQD | DMAC_CHCFG_SEL);
	reg |= (DMAC_CHCFG_TM | (7 << DMAC_CHCFG_DDS_SHIFT) | (7 << DMAC_CHCFG_SDS_SHIFT) |
			(4 << DMAC_CHCFG_AM_SHIFT) |		/* Block Transfer Mode */
			((setting->ch & 0x07) << DMAC_CHCFG_SEL_SHIFT));
	if(setting->rsel == 1)
	{
		reg |= DMAC_CHCFG_RSEL;
	}
	dmac_write_reg(setting->axi_base, DMAC_CHCFG, reg);

	dmac_set_src_addr(setting);
	dmac_set_dst_addr(setting);
	setting->transfer_byte &= 0x3FFFFFFF;			/* Max. 1GByte */
	dmac_write_reg(setting->axi_base, tb_reg_offset[setting->rsel], setting->transfer_byte);

	dmac_write_reg(setting->axi_base, DMAC_CHITVL, 0);

	reg = dmac_read_reg(setting->axi_base, DMAC_CHCTRL);
	reg |= DMAC_CHCTRL_SETEN;
	dmac_write_reg(setting->axi_base, DMAC_CHCTRL, reg);

	/* Set Software Trigger */
	reg = dmac_read_reg(setting->axi_base, DMAC_CHCTRL);
	reg |= DMAC_CHCTRL_STG;
	dmac_write_reg(setting->axi_base, DMAC_CHCTRL, reg);

	while(1)
	{
		reg = dmac_read_reg(setting->axi_base, DMAC_CHSTAT);
		if((reg & (DMAC_CHSTAT_TACT | DMAC_CHSTAT_EN)) == 0)
		{
			if((reg & DMAC_CHSTAT_ER) == DMAC_CHSTAT_ER)
			{
				err_code = DMAC_ERRCODE_ERROR;
			}
			else
			{
				err_code = DMAC_ERRCODE_SUCCESS;
			}
			break;
		}
	}
	return err_code;
}
