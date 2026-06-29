/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SYSC_H__
#define __SYSC_H__

unsigned int sysc_get_device_id(void);
unsigned int sysc_get_device_info(void);

#define	RZG2L_DEVID	(0x841C447)
#define	RZG2UL_DEVID	(0x8450447)

#endif	/* __SYSC_H__ */
