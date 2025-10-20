/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <rz_soc_def.h>
#include <lib/mmio.h>

#define WDT1_WDTRR    (*(volatile uint8_t *)(RZG3E_WDT_CA55_BASE + 0x00))
#define WDT1_WDTCR    (*(volatile uint16_t*)(RZG3E_WDT_CA55_BASE + 0x02))
#define WDT1_WDTRCR   (*(volatile uint8_t *)(RZG3E_WDT_CA55_BASE + 0x06))

void wdt_reset(void)
{
	/*
	 *	Timeout period: 16384 cycles
	 *	Clock division ratio: LOCO clock /128
	 *	Window end position: 0%
	 *	Window start position: 100%
	 */
	WDT1_WDTCR = 0x33F3;
	/* Enable WDT1 interrupt */
	WDT1_WDTRCR = 0x00;
	/* Refresh once for WDT to start counting */
	WDT1_WDTRR = 0x00;
	WDT1_WDTRR = 0xFF;
}
