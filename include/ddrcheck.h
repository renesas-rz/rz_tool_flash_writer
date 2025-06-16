/*
 * Copyright (c) 2019-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

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

void dgDdrLoadParam(void);
void dgDdrTest(void);
void dgRamTest(void);
