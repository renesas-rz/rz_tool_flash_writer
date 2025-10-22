/*
 * Copyright (c) 2015-2024, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <soc_info.h>
#include "common.h"
#include "dgtable.h"
#include "dgmodul4.h"
#include "ramckmdl.h"
#include "devdrv.h"
#include "dgmodul1.h"
#include "bit.h"
#include "xspiflash1drv.h"

uint32_t	gUserPrgStartAdd;
uint32_t	gUserPrgSize;

uint32_t	gManufacturerId;
uint32_t	gDeviceId;
uint32_t	gQspi_sa_size;
uint32_t	gQspi_end_addess;

extern char gKeyBuf[64];

static char dgLS_Load_Offset(uint32_t *maxADD ,uint32_t *minADD, uint32_t prgStatAdd);

//////////////////////////////////////////
// CheckQspiFlashId
//////////////////////////////////////////
static uint32_t CheckQspiFlashId(void)
{
	char		str[64];
	uint32_t	readDevId, ret = 0;
	uint8_t		manuId;
	uint16_t	deviceId;

	ReadQspiFlashID(&readDevId);

	manuId   = readDevId & 0x000000ff;
	deviceId = (readDevId & 0x0000ff00) | ((readDevId >> 16) & 0xff);

	gManufacturerId	= manuId;
	gDeviceId		= deviceId;
	switch(manuId)
	{
		case CYPRESS_MANUFACTURER_ID:
			PutStr(" Cypress : ", 0);
			switch(deviceId)
			{
				case DEVICE_ID_S25FS512S:
						PutStr("S25FS512S", 1);
						gQspi_sa_size    = SA_256KB;
						gQspi_end_addess = TOTAL_SIZE_64MB - 0x8000 - 1;
				break;
				case DEVICE_ID_S25FS128S:
						PutStr("S25FS128S", 1);
						gQspi_sa_size    = SA_256KB;
						gQspi_end_addess = TOTAL_SIZE_16MB - 0x8000 - 1;
				break;
				default:
					ret = 1;
				break;
			}
		break;
		case WINBOND_MANUFACTURER_ID:
			PutStr(" Winbond : ", 0);
			switch(deviceId)
			{
				case DEVICE_ID_W25Q64JV:
						PutStr("W25Q64JV", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_8MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25Q64JW:
						PutStr("W25Q64JW", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_8MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25Q128JV:
						PutStr("W25Q128JV", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_16MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25Q128JW:
						PutStr("W25Q128JW", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_16MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25Q256:
						PutStr("W25Q256", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25Q256JW:
						PutStr("W25Q256JW", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25M512JV:
						PutStr("W25M512JV", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25M512JW:
						PutStr("W25M512JW", 1);
						gQspi_sa_size    = SA_64KB;

						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25Q512JV:
						PutStr("W25Q512JV", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_64MB - 0x8000 - 1;
				break;
				case DEVICE_ID_W25Q512JV_DTR:
						PutStr("W25Q512JV-DTR", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_64MB - 0x8000 - 1;
				break;
				default:
					ret = -1;
				break;
			}
		break;
		case MACRONIX_MANUFACTURER_ID:
			PutStr(" Macronix : ", 0);
			switch(deviceId)
			{
				case DEVICE_ID_MX25L12805:
						PutStr("MX25L12805", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_16MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MX25L25645G:
						PutStr("MX25L25645G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MX25L51245G:
						PutStr("MX25L51245G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_64MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MX66U25635F:
						PutStr("MX66U25635F", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MX66U51235F:
						PutStr("MX66U51235F", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_64MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MX66UM1G45G:
						PutStr("MX66UM1G45G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_128MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MX66UW1G45G:
						PutStr("MX66UW1G45G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_128MB - 0x8000 - 1;
				break;
				default:
					ret = -1;
				break;
			}
		break;
		case MICRON_MANUFACTURER_ID:
			PutStr(" Micron : ", 0);
			switch(deviceId)
			{
				case DEVICE_ID_MT25QL128:
						PutStr("MT25QL128", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_16MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QU128:
						PutStr("MT25QU128", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_16MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QL256:
						PutStr("MT25QL256", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QU256:
						PutStr("MT25QU256", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_32MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QL512:
						PutStr("MT25QL512", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_64MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QU512:
						PutStr("MT25QU512", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_64MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QL01G:
						PutStr("MT25QL01G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_128MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QU01G:
						PutStr("MT25QU01G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_128MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QL02G:
						PutStr("MT25QL02G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_256MB - 0x8000 - 1;
				break;
				case DEVICE_ID_MT25QU02G:
						PutStr("MT25QU02G", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_256MB - 0x8000 - 1;
				break;
				default:
					ret = -1;
				break;
			}
		break;
		case DIALOG_MANUFACTURER_ID:
			PutStr(" Dialog : ", 0);
			switch(deviceId)
			{
				case DEVICE_ID_AT25QL128A:
						PutStr("AT25QL128A", 1);
						gQspi_sa_size    = SA_64KB;
						gQspi_end_addess = TOTAL_SIZE_16MB - 0x8000 - 1;
				break;
				default:
					ret = -1;
				break;
			}
		break;
		default:
			ret = 1;
		break;
	}
	if (ret)
	{
		Data2HexAscii(readDevId, str, 4);
		PutStr(" FlashID = 0x", 0);
		PutStr(str, 1);
	}
	return ret;
}

//////////////////////////////////////////
// SetData
//////////////////////////////////////////
static void SetData(uint32_t *setAdd)
{
	char		buf[16], key[16], chCnt,chPtr;
	uint32_t	loop;
	uint32_t 	wrData;

	loop = 1;

	while(loop)
	{
		PutStr(" Set Data : ",0);
		GetStr(key, &chCnt);
		chPtr = 0;
		if (!GetStrBlk(key, buf, &chPtr, 0))
		{
			if (chPtr == 1)
			{
				/* Case Return */
			}
			else if (chPtr > (char)((SIZE_32BIT<<1)+1))
			{
				/* Case Data Size Over */
				PutStr("Syntax Error", 1);
			}
			else
			{
				if (HexAscii2Data((unsigned char*)buf, &wrData))
				{
					PutStr("Syntax Error", 1);
				}
				else
				{
					*setAdd = wrData;
					loop = 0;
				}
			}
		}
		else
		{
			PutStr("Syntax Error", 1);
		}
	}
}

//////////////////////////////////////////
// SetAddInputKey
//////////////////////////////////////////
static void SetAddInputKey(uint32_t *Address)
{
	char		str[64];
	char		buf[16],key[16],chCnt,chPtr;
	uint32_t	loop;
	uint32_t	wrData;

	loop = 1;
	while(loop)
	{
		PutStr("  Please Input : H'",0);
		GetStr(key,&chCnt);
		chPtr = 0;
		if (!GetStrBlk(key,buf,&chPtr,0))
		{
			if (chPtr == 1)
			{
				/* Case Return */
			}
			else if((buf[0]=='.'))
			{
				/* Case End */
				gUserPrgStartAdd = 0x40000000;
				loop = 0;
			}
			else if (chPtr > (char)((SIZE_32BIT<<1)+1))
			{
				/* Case Data Size Over */
				PutStr("Syntax Error",1);
			}
			else
			{
				if (HexAscii2Data((unsigned char*)buf,&wrData))
				{
					PutStr("Syntax Error",1);
				}
				else
				{
					if (wrData & 0x00000003)
					{
						PutStr("Memory Boundary Error",1);
					}
					else
					{
						*Address = wrData;
						loop = 0;
					}
				}
			}
		}
		else
		{
			PutStr("Syntax Error",1);
		}
	}
}


//////////////////////////////////////////
// SetSizeInputKey
//////////////////////////////////////////
static void SetSizeInputKey(uint32_t *size)
{
	char		str[64];
	char		buf[16],key[16],chCnt,chPtr;
	uint32_t	loop;
	uint32_t	wrData;

	loop = 1;
	while(loop)
	{
		PutStr("  Please Input : H'",0);
		GetStr(key,&chCnt);
		chPtr = 0;
		if (!GetStrBlk(key,buf,&chPtr,0))
		{
			if (chPtr == 1)
			{
				/* Case Return */
			} else if ((buf[0]=='.'))
			{
				/* Case End */
				loop = 0;
			}
			else if (chPtr > (char)((SIZE_32BIT<<1)+1))
			{
				/* Case Data Size Over */
				PutStr("Syntax Error",1);
			}
			else
			{
				if (HexAscii2Data((unsigned char*)buf,&wrData))
				{
					PutStr("Syntax Error",1);
				}
				else
				{
					*size = wrData;
					loop  = 0;
				}
			}
		}
		else
		{
			PutStr("Syntax Error",1);
		}
	}
}

/********************************************************
	MODULE			: dgClearSpiflash0	*
	FUNCTION		: Clear Spiflash memory	*
	COMMAND			: CS			*
	INPUT PARAMETER		: CS			*
*********************************************************/
void dgClearSpiflash0(void)
{
	uint32_t	readManuId,readDevId;
	int32_t		Rtn;

	Rtn = NORMAL_END;

	PutStr("ALL ERASE SpiFlash memory ", 1);
	PutStr("Clear OK?(y/n)", 0);
	if (WaitKeyIn_YorN())
	{
		// Return1=N
		DelStr(14);
		return;
	}
	DelStr(14);
	Init_xSPIFlash();

	if (CheckQspiFlashId())
	{
		return;		//Error abortt
	}
	PutStr(" ERASE QSPI-FLASH (60sec[typ])....",0);
	ChipEraseQspiFlash();
	PutStr(" complete!", 1);
}

//////////////////////////////////////////
// XLoadSpiflash0_2
//////////////////////////////////////////
static void XLoadSpiflash0_2(uint32_t mode)
{
#if INTERNAL_MEMORY_ONLY == 0
	if (f_ddr_param_initialized == 0)
	{
		PutStr("DDR not initialized, please send DDR parameters via \'DDRP\' command", 1);
		return;
	}
#endif /* INTERNAL_MEMORY_ONLY = 0 */
	char		str[64];
	uint32_t	PrgSpiStartAdd, PrgSpiEndAdd, PrgSpiSize, UserPrgStatAdd;
	uint32_t	workAdd_Min, workAdd_Max;
	uintptr_t	Load_workStartAdd;

	PutStr("===== Qspi writing of "SOC_NAME" Board Command =============",1);
	PutStr("Load Program to Spiflash",1);
	PutStr("Writes to any of SPI address.",1);
	Init_xSPIFlash();

	if(CheckQspiFlashId())
	{
		return;
	}

	PutStr((mode == 0U ? "Program Top Address & Qspi Save Address " : "Program size & Qspi Save Address "),1);

	PrgSpiStartAdd	= 0x0;
	PrgSpiSize	= 0x0;

	if (0U == mode)
	{
		PutStr("===== Please Input Program Top Address ============",1);
		SetAddInputKey(&gUserPrgStartAdd);
	}
	else
	{
		PutStr("===== Please Input Program size ============",1);
		SetSizeInputKey(&gUserPrgSize);
	}

	PutStr(" ",1);
	PutStr("===== Please Input Qspi Save Address ===", 1);
	SetAddInputKey(&PrgSpiStartAdd);

	if (gQspi_end_addess < PrgSpiStartAdd)
	{
		PutStr("Address Input Error", 1);
		PutStr("Range of H'000_0000 ~ H'0FF_7FFF", 1);
		return;
	}

	// Load data
	if (0U == mode)
	{
		dgLS_Load_Offset(&workAdd_Max, &workAdd_Min, PrgSpiStartAdd);
	}
	else
	{
		char bin_data;
		uint32_t image_offset = 0U;
		PutStr("please send ! (binary)",1);

		Load_workStartAdd = LS_WORK_MEM_SADD;
		while (image_offset < gUserPrgSize)
		{
			GetChar(&bin_data);
			*(uint8_t *)(Load_workStartAdd + image_offset) = bin_data;
			image_offset++;
		}
		workAdd_Min = Load_workStartAdd;
		workAdd_Max = Load_workStartAdd + gUserPrgSize - 1;
	}

	PutStr("Erase SPI Flash memory...", 1);
	PrgSpiEndAdd = PrgSpiStartAdd + (workAdd_Max - workAdd_Min) - 1;
	EraseQspiFlash(PrgSpiStartAdd, PrgSpiEndAdd);
	PutStr("Write to SPI Flash memory.", 1);
	SaveDataQspiFlash(LS_WORK_MEM_SADD, PrgSpiStartAdd, PrgSpiEndAdd - PrgSpiStartAdd);

	PutStr("======= Qspi  Save Information  =================",1);
	PutStr(" SpiFlashMemory Stat Address : H'",0);
	Data2HexAscii(PrgSpiStartAdd ,str, 4);
	PutStr(str,1);
	PutStr(" SpiFlashMemory End Address  : H'",0);
	Data2HexAscii(PrgSpiEndAdd, str, 4);
	PutStr(str,1);
	PutStr("===========================================================",1);
	PutStr("",1);
}

/************************************************************************
	MODULE			: dgG2LoadSpiflash0_2			*
	FUNCTION		: load Program to Spiflash memory	*
	COMMAND			: XLS2					*
	INPUT PARAMETER		: XLS2					*
*************************************************************************/
void dgG2LoadSpiflash0_2(void)
{
	XLoadSpiflash0_2(0);
}

/************************************************************************
	MODULE			: dgG2LoadSpiflash0_3			*
	FUNCTION		: load Program to Spiflash memory	*
	COMMAND			: XLS3					*
	INPUT PARAMETER		: XLS3					*
*************************************************************************/
void dgG2LoadSpiflash0_3(void)
{
	XLoadSpiflash0_2(1);
}

//////////////////////////////////////////
// dgLS_Load_Offset
//////////////////////////////////////////
static char dgLS_Load_Offset(uint32_t *maxADD ,uint32_t *minADD, uint32_t prgStartAdd)
{
	char		str[12];
	char		dbgstr[64];
	uint32_t	data;
	uint32_t	getByteCount, byteCount;
	uint32_t	loadGetCount,adByteCount,loadGetData,loadGetSum,loadGetCR;
	uint32_t	loadGetAddress, prevLoadAddress;
	uint32_t	loop, loop_S0, s0flag,errFlg, checkData,endFlg;
	uint32_t	workAdd_Min,workAdd_Max;

	uint32_t	payload_size;

	unsigned char *ptr;

	prevLoadAddress = prgStartAdd;

	ptr = (unsigned char *)LS_WORK_MEM_SADD;
	workAdd_Min = LS_WORK_MEM_SADD;
	workAdd_Max = LS_WORK_MEM_SADD;
	loop	= 1;
	loop_S0 = 1;
	errFlg	= 0;
	endFlg	= 0;
	checkData = 0xFF;

	PutStr("please send ! ('.' & CR stop load)",1);
	while(loop)
	{
		loop_S0 = 1;
		s0flag	= 0;
		while(1)
		{
			GetChar(str);
			if (*str == '.' || *str == 's' || *str == 'S')
			{
				break;
			}
		}
		if (*str == '.')
		{
			while(1)
			{
				GetChar(str);
				if (*str == CR_CODE)
				{
					return(1);
				}
			}
		}
		else if (*str == 's' || *str == 'S')
		{
			GetChar(str);
			switch(*str)
			{
				case '0':
					s0flag = 1;
					while(loop_S0)
					{
						GetChar(str);
						if ((*str == CR_CODE) || (*str == LF_CODE))
						{
							loop_S0 = 0;
						}
					}
				break;
				case '1':
					adByteCount = 2;
				break;
				case '2':
					adByteCount = 3;
				break;
				case '3':
					// S3:4Byte Address
					adByteCount = 4;
				break;
				case '7':
				case '8':
				case '9':
					endFlg = 1;
				break;
				default:
					errFlg = 1;
				break;
			}
		}
		if (endFlg == 1 || errFlg == 1)
		{
			while(1)
			{
				GetChar(str);
				if ((*str == CR_CODE) || (*str == LF_CODE))
				{
					*maxADD = workAdd_Max - 1;
					*minADD = workAdd_Min;
					return(0);
				}
			}
		}
		if (s0flag == 0)
		{
			// Payload size
			GetStr_ByteCount(str, 1);
			HexAscii2Data((unsigned char*)str,&payload_size);
			payload_size = payload_size - adByteCount - 1;

			// Address
			getByteCount   = adByteCount;
			GetStr_ByteCount(str, getByteCount);
			HexAscii2Data((unsigned char*)str,&data);
			loadGetAddress = data;

			// payload 
			getByteCount = 1;
			for(int i = 0; i < payload_size; i++ ) 
			{
				GetStr_ByteCount(str, getByteCount);
				HexAscii2Data((unsigned char*)str, &data);
				loadGetAddress++;
				*ptr = (unsigned char)data;
				ptr++;
				workAdd_Max++;
			}

			//Get sum
			getByteCount = 1;
			GetStr_ByteCount(str, getByteCount);
			HexAscii2Data((unsigned char*)str,&data);
			loadGetSum	 = data;
			//Get CR code
			GetChar(str);
			loadGetCR = *str;
			if ((loadGetCR == CR_CODE) || (loadGetCR == LF_CODE))
			{
				loop=1;
			}
		}
	}
}
