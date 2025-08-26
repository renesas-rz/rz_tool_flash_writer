/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <rz_soc_def.h>
#include "tzc_400.h"

static void tzc_init(uint32_t unit, uint32_t ch)
{
	TZC_REGION_ATTR0(unit,ch) 			= 0x0000000F;	//0x110
	TZC_REGION_ID_ACCESS0(unit,ch) 		= 0x000F000F;	//0x114
	TZC_GATE_KEEPER(unit,ch) 			= 0x0000000F;	//0x008
	TZC_GATE_SPECULATION_CTRL(unit,ch)	= 0x00000003;	//0x00C
}

/**********************************************************************************************************************
 * Function Name: init_tzc_400_xspi
 * Description  : Initialize TAC-400 for xSPI.
 * Arguments    : none.
 * Return Value : none.
 *********************************************************************************************************************/
void init_tzc_400_xspi(void)
{
	tzc_init(1, 1);	// xSPI area access approve
}

/**********************************************************************************************************************
 * Function Name: init_tzc_400_ddr
 * Description  : Initialize TAC-400 for DDR.
 * Arguments    : none.
 * Return Value : none.
 *********************************************************************************************************************/
void init_tzc_400_ddr(void)
{
	tzc_init(0, 0);		// DDR0_0
	tzc_init(0, 1);		// DDR0_1
}
