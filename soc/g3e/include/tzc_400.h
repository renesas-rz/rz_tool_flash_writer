/*
 * Copyright (c) 2022-2024, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef DRIVERS_TZC_400_INC_TZC_400_H_
#define DRIVERS_TZC_400_INC_TZC_400_H_

#define TZC_MAX_CH					(7)
#define	TZC_BASE(n)	\
	( (n) == 0 ? TZC_BASEADDR_ACPU : TZC_BASEADDR_MCPU)
#define TZC_BASEADDR_ACPU   ((uintptr_t)0x13C60000)
#define TZC_BASEADDR_MCPU   ((uintptr_t)0x10460000)

#define TZC_GATE_KEEPER(n,c)			 (*((volatile uint32_t *)((TZC_BASE(n) + (0x10000 * c)) + 0x008)))
#define TZC_GATE_SPECULATION_CTRL(n,c)   (*((volatile uint32_t *)((TZC_BASE(n) + (0x10000 * c)) + 0x00C)))
#define TZC_REGION_ATTR0(n,c)			 (*((volatile uint32_t *)((TZC_BASE(n) + (0x10000 * c)) + 0x110)))
#define TZC_REGION_ID_ACCESS0(n,c)	     (*((volatile uint32_t *)((TZC_BASE(n) + (0x10000 * c)) + 0x114)))

extern void init_tzc_400_xspi(void);
extern void init_tzc_400_ddr(void);

#endif /* DRIVERS_TZC_400_INC_TZC_400_H_ */
