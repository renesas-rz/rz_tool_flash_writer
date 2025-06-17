/*
 * Copyright (c) 2019-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __DDRCHECK_H__
#define __DDRCHECK_H__

#define MC_ODT_PINS_TBL_NUM 4
#define MC_MR1_TBL_NUM      2
#define MC_MR2_TBL_NUM      2
#define MC_MR5_TBL_NUM      2
#define MC_MR6_TBL_NUM      2
#define DDR_AN_VERSION_NUM  2

/* DDR parameters binary size of RZ/G2L only  */
#define DDR_PARAM_FIXED_SIZE (MC_ODT_PINS_TBL_NUM + MC_MR1_TBL_NUM + \
                            MC_MR2_TBL_NUM + MC_MR5_TBL_NUM + MC_MR6_TBL_NUM + \
                            MC_PHYSET_NUM*2 + SWIZZLE_MC_NUM*2 + SIZZLE_PHY_NUM*2 + \
                            DDR_AN_VERSION_NUM + MC_INIT_NUM *2)*4

#if (RZG2L == 1)
#define DDR_MEM_START_ADDRESS   0x40000040
#define DDR_MEM_END_ADDRESS     0x13FFFFFFF
#else
#define DDR_MEM_START_ADDRESS   0x40000040
#define DDR_MEM_END_ADDRESS     0x13FFFFFFF
#endif

void dgDdrLoadParam(void);
void dgDdrTest(void);
void dgDdrSimple(void);
void dgDdrRandb(void);
void dgDdrFixedb(void);
void dgDdrEyeOpenTool(void);

#endif /*__DDRCHECK_H__*/