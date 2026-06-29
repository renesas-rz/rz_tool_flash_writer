/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sysc.h"
#include <ddr_internal.h>

static void ddr_ctrl_reten_en_n_g2l(uint8_t val)
{
	if (sysc_get_device_info() > 1)
	{
		val &= 1;
		write_phy_reg(DDRPHY_R79, (val << 1));
	}
	else
	{
		val &= 1;
		rmw_phy_reg(DDRPHY_R78, 0xFFFEFFFF, (val << 16));
	}
}

static void ddr_ctrl_reten_en_n_g2ul(uint8_t val)
{
	val &= 1;
	write_phy_reg(DDRPHY_R79, (val << 1));
}

void ddr_ctrl_reten_en_n(uint8_t val)
{
	unsigned int deviceid;

	deviceid = sysc_get_device_id();

	switch(deviceid)
	{
		case RZG2L_DEVID:
			ddr_ctrl_reten_en_n_g2l(val);
		break;
		case RZG2UL_DEVID:
			ddr_ctrl_reten_en_n_g2ul(val);
		break;
		default:
		break;
	}
}
