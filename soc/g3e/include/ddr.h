/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DDR_H__
#define __DDR_H__

#include <stdbool.h>

#define	RET_CSR_SIZE		0x400
#define	DDR_SETUP			ddr_setup
extern uint32_t ddr_csr_table[RET_CSR_SIZE];

void ddr_setup(void);
void ddr_retention_entry(void);
void ddr_retention_exit(void);

#endif	/* __DDR_H__ */
