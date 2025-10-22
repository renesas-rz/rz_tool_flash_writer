/*
 * Copyright (c) 2015-2016, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Status of DDR Parameters initialized or not */
extern uint8_t f_ddr_param_initialized;

int32_t PutChar(char outChar);
int32_t GetChar(char *inChar);
int32_t WaitPutCharSendEnd(void);
