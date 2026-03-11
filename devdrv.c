/*
 * Copyright (c) 2015-2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common.h"
#include "devdrv.h"
#include "scifdrv.h"
#if (USB_ENABLE == 1)
#include "r_usb_drv.h"
#endif
/********************
	PutChar			*
*********************/

int32_t PutChar(char outChar)
{
#if (USB_ENABLE == 1)
	r_drv_usb_putchar(outChar);
#else
	PutCharSCIF0(outChar);
#endif
	return(0);
}

/********************
	GetChar			*
*********************/

int32_t GetChar(char *inChar)
{
#if (USB_ENABLE == 1)
	r_drv_usb_getchar(inChar, 0);
#else
	GetCharSCIF0(inChar);
#endif
	return(0);
}

int32_t WaitPutCharSendEnd(void)
{
#if (USB_ENABLE == 0)
    WaitPutScif0SendEnd();
#endif
}
