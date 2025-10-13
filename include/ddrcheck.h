/*
 * Copyright (c) 2019-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DDRCHECK_H__
#define __DDRCHECK_H__

#define DDR_MEM_START_ADDRESS   0x40000000
#define DDR_MEM_END_ADDRESS     0x23FFFFFFF

void dgDdrLoadParam(void);
void dgDdrTest(void);
void dgDdrSimple(void);
void dgDdrRandb(void);
void dgDdrFixedb(void);

#endif /*__DDRCHECK_H__*/