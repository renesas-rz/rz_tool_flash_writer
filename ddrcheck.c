/*
 * Copyright (c) 2015-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma GCC optimize ("Og")

#include <soc_info.h>
#include "common.h"
#include "dgtable.h"
#include "ramckmdl.h"
#include "devdrv.h"
#include "ddrcheck.h"
#include "ddr.h"

uintptr_t	gErrDdrAdd;
uint32_t	gErrDdrData,gTrueDdrData;
uintptr_t	gSubErrAdd;
uintptr_t	gSubErrData;
uintptr_t	gSubTrueData;

extern char gKeyBuf[64];

static uint32_t PutDdrErrInfo(void)
{
	char str[64];

	PutStr(" error address  : H'",0);	Data2HexAscii_64(gErrDdrAdd,str,CPU_BYTE_SIZE);	PutStr(str,1);
	PutStr(" error data     : H'",0);	Data2HexAscii(gErrDdrData,str,4);	PutStr(str,1);
	PutStr(" true  data     : H'",0);	Data2HexAscii(gTrueDdrData,str,4);	PutStr(str,1);
}

static uint32_t CkExtendDdrRamCheck(void* ramAddr)
{
	volatile uint32_t *read_adr;
	uint32_t data;
	uint32_t loop, i;
	char str[64];

	read_adr = (uint32_t *)ramAddr;

	PutStr("Data=0x5A5A5A5A",0);

	/* Write */
	data = 0x5A5A5A5A;
	for (loop = 0; loop < 0x100000; loop++)
	{
		read_adr[loop] = data;
	}
	/* Verify */
	data = 0x5A5A5A5A;
	for (loop = 0; loop < 0x100000; loop++)
	{
		if (read_adr[loop] != data)
		{
			gErrDdrAdd   = (uintptr_t)&read_adr[loop];
			gErrDdrData  = read_adr[loop];
			gTrueDdrData = data;
			return(ERROR_END);
		}
	}
	DelStr(15);
	PutStr("Data=0xA5A5A5A5",0);

	/* Write */
	data = 0xA5A5A5A5;
	for (loop = 0; loop < 0x100000; loop++)
	{
		read_adr[loop] = data;
	}
	/* Verify */
	data = 0xA5A5A5A5;
	for (loop = 0; loop < 0x100000; loop++)
	{
		if (read_adr[loop] != data)
		{
			gErrDdrAdd   = (uintptr_t)&read_adr[loop];
			gErrDdrData  = read_adr[loop];
			gTrueDdrData = data;
			return(ERROR_END);
		}
	}
	DelStr(15);
	PutStr("Data=0x12345678",0);
 
	/* Write */
	data = 0x12345678;
	for (loop = 0; loop < 0x100000; loop++)
	{
		read_adr[loop] = data;
		data += 0x11111111;
	}
	/* Verify */
	data = 0x12345678;
	for (loop = 0; loop < 0x100000; loop++)
	{
		if (read_adr[loop] != data)
		{
			gErrDdrAdd   = (uintptr_t)&read_adr[loop];
			gErrDdrData  = read_adr[loop];
			gTrueDdrData = data;
			return(ERROR_END);
		}
		data += 0x11111111;
	}
	DelStr(15);
	return(NORMAL_END);
}

static int32_t CheckAndFillData8Bit( uint8_t *startAddr, uint8_t *endAddr, uint8_t writeData, uint8_t checkData )
{
	volatile uint8_t *pData;
	pData = (uint8_t *)startAddr;
	while(1)
	{
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (*pData!=checkData) break;  *(pData++) = writeData;
		if (pData >= endAddr)  return NORMAL_END;
	}
	gSubErrAdd   = (uint64_t)pData;
	gSubErrData  = (uint64_t)*pData;
	gSubTrueData = (uint64_t)checkData;
	return ERROR_END;
}

static int32_t FillData8Bit(uint8_t *startAddr, uint8_t *endAddr, uint8_t writeData)
{
	volatile uint8_t *pData;
	pData = (uint8_t *)startAddr;
	while(1){
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		*(pData++) = writeData;
		if( pData >= endAddr )  return NORMAL_END;
	}
	return NORMAL_END;
}

static int32_t CheckData8Bit( uint8_t *startAddr, uint8_t *endAddr, uint8_t checkData )
{
	volatile uint8_t *pData;
	pData = (uint8_t *)startAddr;
	while(1)
	{
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if(*(pData++)!=checkData) break;
		if (pData >= endAddr)  return NORMAL_END;
	}
	pData--;
	gSubErrAdd   = (uint64_t)pData;
	gSubErrData  = (uint64_t)*pData;
	gSubTrueData = (uint64_t)checkData;
	return ERROR_END;
}

static int32_t WriteIncData8Bit( uint8_t *startAddr, uint8_t *endAddr, uint8_t startData )
{
	volatile uint8_t *pData;
	pData = (uint8_t *)startAddr;
	while(1)
	{
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		*(pData++) = (startData++);
		if (pData >= endAddr)  return NORMAL_END;
	}
	return NORMAL_END;
}

static int32_t CheckIncData8Bit( uint8_t *startAddr, uint8_t *endAddr, uint8_t startData )
{
	volatile uint8_t *pData;
	pData = (uint8_t *)startAddr;
	while(1)
	{
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if(*(pData++)!=(startData++)) break;
		if( pData >= endAddr )  return NORMAL_END;
	}
	pData--;
	startData--;
	gSubErrAdd   = (uint64_t)pData;
	gSubErrData  = (uint64_t)*pData;
	gSubTrueData = (uint64_t)startData;
	return ERROR_END;
}

static char DecodeForm5(uintptr_t *para1st, uintptr_t *para2nd, uint32_t *setPara)
{
	char tmp[64],tmp2[64],chPtr,chPtr2,endCh,getCnt,value;
	uintptr_t tmpData;

	*setPara = 0;
	chPtr = getCnt = 0;
	do
	{
		endCh = GetStrBlk(gKeyBuf,tmp,&chPtr,0);
		switch(getCnt)
		{
			/*********** "RAMCK" Block parameter  *************/
			case 0:
				if (endCh == 0)
				{
					/* non set start Add */
					return(2);
				}
			break;
			/*********** Ana 1st parameter  *******************/
			case 1:
				value = HexAscii2Data_64((unsigned char*)tmp,para1st);
				if (value == 0)
				{
					*setPara |= 0x01;
				}
				else
				{
					return(1);
				}
			break;
			/*********** Ana 2nd parameter  *******************/
		 	case 2:
				value = HexAscii2Data_64((unsigned char*)tmp,&tmpData);
				if (value == 0)
				{
					*setPara |= 0x02;
					if (*para1st > tmpData)
					{
						return(2);
					}
					else
					{
						*setPara |= 0x02;
						*para2nd = (tmpData - *para1st) + 0x01 ;
				 	}
				}
				else if (value == 3)
				{
					/* find @ */
					chPtr2 = 1;
					GetStrBlk(tmp,tmp2,&chPtr2,0);
					if (HexAscii2Data_64((unsigned char*)tmp2,para2nd))
					{
						return(1);
					}
					*setPara |= 0x02;
				}
				else
				{
					return(1);
				}
			break;
		}
		if (endCh == ';')
		{
			if (GetStrBlk(gKeyBuf,tmp,&chPtr,0))
			{
				return(1);
			}
			endCh=0;
			*setPara |= 0x08;
		}
		getCnt++;
	} while(endCh);
	return(0);
}

static int32_t TPRAMCK( uint8_t *startAddr, uint8_t *endAddr )
{
	FillData8Bit(startAddr, endAddr, 0x00 );
	if (CheckAndFillData8Bit(startAddr, endAddr, 0x55, 0x00))
	{
		return ERROR_END;
	}
	if (CheckAndFillData8Bit(startAddr, endAddr, 0xAA, 0x55))
	{
		return ERROR_END;
	}
	if (CheckAndFillData8Bit(startAddr, endAddr, 0xFF, 0xAA))
	{
		return ERROR_END;
	}
	if (CheckData8Bit(startAddr, endAddr, 0xFF))
	{
		return ERROR_END;
	}
	WriteIncData8Bit(startAddr, endAddr, 0x00);
	if (CheckIncData8Bit(startAddr, endAddr, 0x00))
	{
		return ERROR_END;
	}
	return NORMAL_END;
}

static void fill_data_char_arr1D(char *dest, char *src, uint8_t size, uint32_t *offset){
	for (int i = 0; i < size; i++) {
		dest[i] = (char)src[*offset];
		*offset += 1;
	}
}

static void fill_data_arr2D(uint32_t dest[][2], uint8_t *src, uint32_t size, uint32_t *offset) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 2; j++) {
			dest[i][j] = READ_LE32(&src[*offset]);
			*offset += 4;
		}
	}
}

static void fill_data_arr1D(uint16_t *dest, uint8_t *src, uint32_t size, uint32_t *offset){
	uint32_t align8bytes = ALIGN8(size*2);
	for (int i = 0; i < size; i++) {
		dest[i] = READ_LE16(&src[*offset]);
		*offset += 2;
		align8bytes -= 2;
	}
	while (align8bytes > 0) {
		*offset += 2;
		align8bytes -= 2;
	}
}

static uint8_t InputFileSize(uint32_t *fileSize)
{
	uint32_t loop;
	uint32_t wrData;
	int8_t str[16];
	int8_t buf[16];
	int8_t chCnt = 0;
	int8_t chPtr;

	loop = 1;
	while(loop)
	{
		PutStr("Please Input File size(byte) : H'",0);
		GetStr(str,&chCnt);
		chPtr = 0;
		if (!GetStrBlk(str,buf,&chPtr,0))
		{
			if (chPtr == 1)
			{	/* Case Return */
				return(0);
			}
			else
			{
				if (HexAscii2Data((uint8_t*)buf,&wrData))
				{
					PutStr("Syntax Error",1);
				}
				else
				{
					*fileSize = wrData;
					loop = 0;
				}
			}
		}
	}

	return(1);
}

void dgDdrLoadParam(void)
{
	uint32_t offset = 0;
	uint32_t received = 0U;
	uint32_t fileSize, fileSizeCount;
	uint8_t chkInput;
	uint8_t byteData;
	char buf[8];
	static uint8_t ddr_param_buf[DDR_PARAM_MAX_SIZE];

	chkInput = InputFileSize( &fileSize );
	if (1 != chkInput || fileSize < DDR_PARAM_MIN_SIZE || fileSize > DDR_PARAM_MAX_SIZE)
	{
		PutStr("Invalid DDR parameters file size!", 1);
		return;
	}
	PutStr("Please send ! (binary)",1);

	/* Receiving data of DDR parameters */
	while (received < fileSize)
	{
		GetChar(&byteData);
		ddr_param_buf[received++] = byteData;
	}

	/* Extract the last from a binary file to determine the array size */
	param_setup_mc_size = READ_LE32(&ddr_param_buf[fileSize - 32]);
	param_phyinit_c_size = READ_LE32(&ddr_param_buf[fileSize - 28]);
	param_phyinit_1d_dat1_size = READ_LE32(&ddr_param_buf[fileSize - 24]);
	param_phyinit_2d_dat1_size = READ_LE32(&ddr_param_buf[fileSize - 20]);
	param_phyinit_i_size = READ_LE32(&ddr_param_buf[fileSize - 16]);
	param_phyinit_1d_dat0_size = READ_LE32(&ddr_param_buf[fileSize - 12]);
	param_phyinit_2d_dat0_size = READ_LE32(&ddr_param_buf[fileSize - 8]);
	param_phyinit_swizzle_size = READ_LE32(&ddr_param_buf[fileSize - 4]);

	/* Check if the received size matches the value extracted from the binary */
	fileSizeCount = (param_setup_mc_size * 2 + \
					param_phyinit_c_size * 2 + \
					param_phyinit_i_size * 2 + \
					param_phyinit_swizzle_size * 2 + 10) * 4 + \
					ALIGN8(param_phyinit_1d_dat1_size * 2) + \
					ALIGN8(param_phyinit_2d_dat1_size * 2) + \
					ALIGN8(param_phyinit_1d_dat0_size * 2) + \
					ALIGN8(param_phyinit_2d_dat0_size * 2);
	if (fileSizeCount != fileSize)
	{
		PutStr("BIN data structure is INVALID with size(byte) : H\'", 0);
		Data2HexAscii(fileSizeCount, buf, SIZE_32BIT);
		PutStr(buf, 1);
		return;
	}

	/* Load ddr parameters into array local */
	fill_data_char_arr1D(ddr_version_str, ddr_param_buf, 8, &offset);
	fill_data_arr2D(param_setup_mc, ddr_param_buf, param_setup_mc_size, &offset);
	fill_data_arr2D(param_phyinit_c, ddr_param_buf, param_phyinit_c_size, &offset);
	fill_data_arr1D(param_phyinit_1d_dat1, ddr_param_buf, param_phyinit_1d_dat1_size, &offset);
	fill_data_arr1D(param_phyinit_2d_dat1, ddr_param_buf, param_phyinit_2d_dat1_size, &offset);
	fill_data_arr2D(param_phyinit_i, ddr_param_buf, param_phyinit_i_size, &offset);
	fill_data_arr1D(param_phyinit_1d_dat0, ddr_param_buf, param_phyinit_1d_dat0_size, &offset);
	fill_data_arr1D(param_phyinit_2d_dat0, ddr_param_buf, param_phyinit_2d_dat0_size, &offset);
	fill_data_arr2D(param_phyinit_swizzle, ddr_param_buf, param_phyinit_swizzle_size, &offset);

	PutStr("DDR parameters loaded\n", 1);
	PutStr("start DDR Setup", 1);
	DDR_SETUP();
	f_ddr_param_initialized = 1;
}

void dgDdrTest(void)
{
	if (f_ddr_param_initialized == 0)
	{
		PutStr("DDR not initialized, please send DDR parameters via \'DDRP\' command", 1);
		return;
	}

	uint32_t readData, chCnt;
	char	str[16];

	PutStr("=== DDR R/W CHECK ====",1);
	PutStr("=== Memory map "SOC_NAME" ===",1);
	Hex2Ascii((DDR_CHECK_AREA1 >>32) & 0xFF, str, &chCnt);
	PutStr("Check:0x", 0);
	PutStr(&str[6], 0);
	PutStr("_", 0);
	Hex2Ascii(DDR_CHECK_AREA1 & 0xFFFFFFFF, str, &chCnt);
	PutStr(str, 0),
	PutStr(" ... ",0);
	readData = *((volatile uint32_t*)DDR_CHECK_AREA1);	//Access Check
	if (CkExtendDdrRamCheck((void*)DDR_CHECK_AREA1))
	{
		PutStr(" Fail!",1);
		PutDdrErrInfo();
		return;
	}
	else
	{
		PutStr(" Pass!",1);
	}
#if DDR_CHECK_AREA2
	Hex2Ascii((DDR_CHECK_AREA2 >>32) & 0xFF, str, &chCnt);
	PutStr("Check:0x", 0);
	PutStr(&str[6], 0);
	PutStr("_", 0);
	Hex2Ascii(DDR_CHECK_AREA2 & 0xFFFFFFFF, str, &chCnt);
	PutStr(str, 0),
	PutStr(" ... ",0);
	readData = *((volatile uint32_t*)DDR_CHECK_AREA2);	//Access Check
	if (CkExtendDdrRamCheck((void*)DDR_CHECK_AREA2))
	{
		PutStr(" Fail!",1);
		PutDdrErrInfo();
		return;
	}
	else
	{
		PutStr(" Pass!",1);
	}
#endif
}

void dgRamTest(void)
{
	if (f_ddr_param_initialized == 0)
	{
		PutStr("DDR not initialized, please send DDR parameters via \'DDRP\' command", 1);
		return;
	}

	uint64_t ramck1st,ramck2nd;
	uint32_t setPara;

	char decRtn;
	char str[10];

	ramck1st=ramck2nd=0x0;
	decRtn = DecodeForm5(&ramck1st,&ramck2nd,&setPara);
	if (!(setPara&0x3))
	{
		PutStr("Syntax Error",1);	return;
	}
	else if (decRtn==1)
	{
		PutStr("Syntax Error",1);	return;
	}
	else if (decRtn==2)
	{
		PutStr("Address Size Error",1);	return;
	}
	else
	{
		PutStr("== RAM CHECK (Byte Access) ===",1);
		PutStr("- Marching Data Check --------",1);
		PutStr(" [ Write H'00               ]",1);
		PutStr(" [ Check H'00 -> Write H'55 ]",1);
		PutStr(" [ Check H'55 -> Write H'AA ]",1);
		PutStr(" [ Check H'AA -> Write H'FF ]",1);
		PutStr(" [ Check H'FF               ]",1);
		PutStr("- Decoder Pattern Check ------",1);
		PutStr(" [ Write H'00,H'01,H'02 ... ]",1);
		PutStr(" [ Check H'00,H'01,H'02 ... ]",1);
		PutStr("CHECK RESULT",0);
	}
	if (TPRAMCK( ((uint8_t *)ramck1st),((uint8_t *)(ramck1st+ramck2nd)) ) )
	{
		PutStr("---->NG",1);
		Data2HexAscii_64(gSubErrAdd,str,CPU_BYTE_SIZE);
		PutStr("ERROR ADDRESS:",0); PutStr(str,1);
		Data2HexAscii_64(gSubErrData,str,CPU_BYTE_SIZE);
		PutStr("ERROR DATA   :",0); PutStr(str,1);
		Data2HexAscii_64(gSubTrueData,str,CPU_BYTE_SIZE);
		PutStr("TRUE DATA    :",0); PutStr(str,1);
		return;
	}
	else
	{
		PutStr("---->OK",1);
	}
}
