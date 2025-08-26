/*
 * Copyright (c) 2015-2019, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
void Init_xSPIFlash(void);
void EraseQspiFlash(uint32_t EraseStatAddr, uint32_t EraseEndAddr);
void SaveDataQspiFlash(uint32_t srcAdd, uint32_t svFlashAdd, uint32_t svSize);
void ReadQspiFlashID(uint32_t *readData);
void ChipEraseQspiFlash(void);
