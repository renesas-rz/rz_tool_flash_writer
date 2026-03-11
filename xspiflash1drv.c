/*
 * Copyright (c) 2015-2024, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common.h"
#include "bit.h"
#include "xspiflash1drv.h"
#include "r_xspi_drv.h"

#define	DEBUG (0)

void Init_xSPIFlash()
{
	r_drv_xspi_init(XSPI_CH0_SEC, XSPI_MODE_X1_SEC);
}

void EraseQspiFlash(uint32_t EraseStatAddr, uint32_t EraseEndAddr)
{
#if (DEBUG_MSG)
	char		str[64];
#endif
	uint32_t	sectorAd;
	uint32_t	start_addr, end_addr;

	start_addr = EraseStatAddr & 0xFFFFF000;
	end_addr  = EraseEndAddr  & 0xFFFFF000;
#if (DEBUG_MSG)
	PutStr("## ParameterSectorEraseQspiFlash", 1);

	PutStr("Stat address : 0x", 0);
	Data2HexAscii(start_addr, str, 4);
	PutStr(str, 1);
	PutStr("End address : 0x", 0);
	Data2HexAscii(end_addr, str, 4);
	PutStr(str, 1);
#endif
	R_DRV_XSPI_Erase(XSPI_CH0_SEC, start_addr, end_addr - start_addr);
	PutStr("Erase Completed ",1);
}

void SaveDataQspiFlash(uint32_t srcAdd, uint32_t svFlashAdd, uint32_t svSize)
{
#if (DEBUG_MSG)
	char		str[64];
#endif
	uint32_t	flashAdd;
	uint32_t	writeDataAdd;

#if (DEBUG_MSG)
	PutStr("## SaveDataQspiFlash", 1);

	PutStr("srcAdd : 0x", 0);
	Data2HexAscii(srcAdd, str, 4);
	PutStr(str, 1);
	PutStr("svFlashAdd : 0x", 0);
	Data2HexAscii(svFlashAdd, str, 4);
	PutStr(str, 1);
	PutStr("svSize : 0x", 0);
	Data2HexAscii(svSize, str, 4);
	PutStr(str, 1);
#endif

	writeDataAdd = srcAdd;
	for (flashAdd = svFlashAdd; flashAdd<(svFlashAdd+svSize); flashAdd += 256)
	{
		// 256byte:RPC Write Buffer size
		R_DRV_XSPI_Write(XSPI_CH0_SEC, flashAdd, writeDataAdd, 256);
		writeDataAdd = writeDataAdd + 256;
	}
}

void ReadQspiFlashID(uint32_t *readData)
{
	R_DRV_XSPI_ReadId(XSPI_CH0_SEC, readData);
}

void ChipEraseQspiFlash(void)
{
	R_DRV_XSPI_ChipErase(XSPI_CH0_SEC);
}
