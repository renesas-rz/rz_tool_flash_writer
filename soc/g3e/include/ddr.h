/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DDR_H__
#define __DDR_H__

#include <stdbool.h>

#define	RET_CSR_SIZE		0x400
#define	DDR_SETUP			ddr_setup
extern uint32_t ddr_csr_table[RET_CSR_SIZE];

#define DDR_VERSION_STR           8

/* RZG3E >>> */
#define PARAM_SETUP_MC        776
#define PARAM_PHYINIT_C_MIN   86
#define PARAM_PHYINIT_1D_DAT1 830
#define PARAM_PHYINIT_2D_DAT1 704
#define PARAM_PHYINIT_I       565
#define PARAM_PHYINIT_1D_DAT0 16319
#define PARAM_PHYINIT_2D_DAT0 12892
#define PARAM_PHYINIT_SWIZZLE 44

#define PARAM_PHYINIT_C_MAX   100
/* <<< RZG3E */

#define ALIGN8(x)   (((x) + 7) & ~7U)

#define DDR_PARAM_MIN_SIZE  (((PARAM_SETUP_MC) * 2 + (PARAM_PHYINIT_C_MIN) * 2 + \
                            (PARAM_PHYINIT_I) * 2 + (PARAM_PHYINIT_SWIZZLE) * 2 + 10) * 4 + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT1) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT1) * 2) + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT0) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT0) * 2))

#define DDR_PARAM_MAX_SIZE  (((PARAM_SETUP_MC) * 2 + (PARAM_PHYINIT_C_MAX) * 2 + \
                            (PARAM_PHYINIT_I) * 2 + (PARAM_PHYINIT_SWIZZLE) * 2 + 10) * 4 + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT1) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT1) * 2) + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT0) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT0) * 2))

#define READ_LE32(p) ( \
    ((uint32_t)(p)[0])       | \
    ((uint32_t)(p)[1] << 8)  | \
    ((uint32_t)(p)[2] << 16) | \
    ((uint32_t)(p)[3] << 24) )

#define READ_LE16(p) ( \
    ((uint32_t)(p)[0])       | \
    ((uint32_t)(p)[1] << 8) )

extern uint32_t ddr_csr_table[RET_CSR_SIZE];

extern char ddr_version_str[DDR_VERSION_STR];
extern uint32_t param_setup_mc[PARAM_SETUP_MC][2];
extern uint32_t param_phyinit_c[PARAM_PHYINIT_C_MAX][2];
extern uint16_t param_phyinit_1d_dat1[PARAM_PHYINIT_1D_DAT1];
extern uint16_t param_phyinit_2d_dat1[PARAM_PHYINIT_2D_DAT1];
extern uint32_t param_phyinit_i[PARAM_PHYINIT_I][2];
extern uint16_t param_phyinit_1d_dat0[PARAM_PHYINIT_1D_DAT0];
extern uint16_t param_phyinit_2d_dat0[PARAM_PHYINIT_2D_DAT0];
extern uint32_t param_phyinit_swizzle[PARAM_PHYINIT_SWIZZLE][2];

extern uint32_t param_setup_mc_size;
extern uint32_t param_phyinit_c_size;
extern uint32_t param_phyinit_1d_dat1_size;
extern uint32_t param_phyinit_2d_dat1_size;
extern uint32_t param_phyinit_i_size;
extern uint32_t param_phyinit_1d_dat0_size;
extern uint32_t param_phyinit_2d_dat0_size;
extern uint32_t param_phyinit_swizzle_size;

void ddr_setup(void);
void ddr_retention_entry(void);
void ddr_retention_exit(void);

#endif	/* __DDR_H__ */
