/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <rz_soc_def.h>
#include <lib/mmio.h>

#define	WDTCNT0	(RZG3E_WDT_CA55_BASE + 0x00)
#define	WDTSET0	(RZG3E_WDT_CA55_BASE + 0x04)

void wdt_reset(void)
{
	*((volatile uint32_t*)WDTSET0) = 0x001FFFFF;
	*((volatile uint32_t*)WDTCNT0) = 0x01;
}
