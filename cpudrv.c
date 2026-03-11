/*
 * Copyright (c) 2015-2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common.h"
#include "bit.h"
#include "cpudrv.h"
#include "timer.h"

void StartTMU0(uint32_t tenmSec)
{
    ostm_wait_timer_ms(tenmSec);
}

void StartTMU0usec(uint32_t tenuSec)
{
    ostm_wait_timer_us(tenuSec);
}

void udelay(uint32_t count_us)
{
	StartTMU0usec(count_us);
}

void PowerOnTmu0(void)
{
}
