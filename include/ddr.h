/*
 * Copyright (c) 2020, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DDR_H__
#define __DDR_H__

#include <ddr_internal.h>
#include "dmac.h"

extern uint32_t mc_odt_pins_tbl[4];
extern uint32_t mc_mr1_tbl[2];
extern uint32_t mc_mr2_tbl[2];
extern uint32_t mc_mr5_tbl[2];
extern uint32_t mc_mr6_tbl[2];
extern uint32_t mc_phy_settings_tbl[MC_PHYSET_NUM][2];
extern uint32_t swizzle_mc_tbl[SWIZZLE_MC_NUM][2];
extern uint32_t swizzle_phy_tbl[SIZZLE_PHY_NUM][2];
extern char ddr_an_version[8];
extern uint32_t mc_init_tbl[MC_INIT_NUM][2];

typedef enum {
	OPT_DELAY_SKIP = 0,
	OPT_DELAY_RUN  = 1
} opt_delay_flg_t;

typedef struct {
	const uint64_t	*p_wr_pattern;
	uint32_t		*p_wr_pattern_inv;
	uint32_t		*p_rd_buf;
	uint32_t		pattern_bytes;
} open_eye_memory_t;

void ddr_setup(opt_delay_flg_t runOptDelay);
void ddr_eye_open_tool(open_eye_memory_t *mem, dmac_setting_t *dmac);

#endif	/* __DDR_H__ */
