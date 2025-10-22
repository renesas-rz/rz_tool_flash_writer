/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DDR_H__
#define __DDR_H__
#include <stdint.h>
#include <stddef.h>

#define	RET_CSR_SIZE		0x400
#define	DDR_SETUP			ddr_setup

#define DDR_VERSION_STR           8

/* RZG3S >>> */
#define PARAM_SETUP_MC_MIN        689
#define PARAM_PHYINIT_C_MIN       70
#define PARAM_PHYINIT_1D_DAT1_MIN 830
#define PARAM_PHYINIT_2D_DAT1_MIN 702
#define PARAM_PHYINIT_I_MIN       188
#define PARAM_PHYINIT_1D_DAT0_MIN 13668
#define PARAM_PHYINIT_2D_DAT0_MIN 12728
#define PARAM_PHYINIT_SWIZZLE_MIN 22

#define PARAM_SETUP_MC_MAX        689
#define PARAM_PHYINIT_C_MAX       100
#define PARAM_PHYINIT_1D_DAT1_MAX 870
#define PARAM_PHYINIT_2D_DAT1_MAX 738
#define PARAM_PHYINIT_I_MAX       700
#define PARAM_PHYINIT_1D_DAT0_MAX 16181
#define PARAM_PHYINIT_2D_DAT0_MAX 14238
#define PARAM_PHYINIT_SWIZZLE_MAX 22
/* <<< RZG3S */

#define ALIGN8(x)   (((x) + 7) & ~7U)

#define DDR_PARAM_MIN_SIZE  (((PARAM_SETUP_MC_MIN) * 2 + (PARAM_PHYINIT_C_MIN) * 2 + \
                            (PARAM_PHYINIT_I_MIN) * 2 + (PARAM_PHYINIT_SWIZZLE_MIN) * 2 + 10) * 4 + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT1_MIN) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT1_MIN) * 2) + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT0_MIN) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT0_MIN) * 2))

#define DDR_PARAM_MAX_SIZE  (((PARAM_SETUP_MC_MAX) * 2 + (PARAM_PHYINIT_C_MAX) * 2 + \
                            (PARAM_PHYINIT_I_MAX) * 2 + (PARAM_PHYINIT_SWIZZLE_MAX) * 2 + 10) * 4 + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT1_MAX) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT1_MAX) * 2) + \
                            ALIGN8((PARAM_PHYINIT_1D_DAT0_MAX) * 2) + \
                            ALIGN8((PARAM_PHYINIT_2D_DAT0_MAX) * 2))

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
extern uint32_t param_setup_mc[PARAM_SETUP_MC_MAX][2];
extern uint32_t param_phyinit_c[PARAM_PHYINIT_C_MAX][2];
extern uint16_t param_phyinit_1d_dat1[PARAM_PHYINIT_1D_DAT1_MAX];
extern uint16_t param_phyinit_2d_dat1[PARAM_PHYINIT_2D_DAT1_MAX];
extern uint32_t param_phyinit_i[PARAM_PHYINIT_I_MAX][2];
extern uint16_t param_phyinit_1d_dat0[PARAM_PHYINIT_1D_DAT0_MAX];
extern uint16_t param_phyinit_2d_dat0[PARAM_PHYINIT_2D_DAT0_MAX];
extern uint32_t param_phyinit_swizzle[PARAM_PHYINIT_SWIZZLE_MAX][2];

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
