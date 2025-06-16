/*
 * Copyright (c) 2015-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma GCC optimize ("Og")

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

void dgDdrTest(void)
{
	if (f_ddr_param_initialized == 0)
	{
		PutStr("DDR not initialized, please send DDR parameters via \'DDRP\' command", 1);
		return;
	}

	uint32_t readData;
	PutStr("=== DDR R/W CHECK ====",1);
#if (RZG2L == 1)
	PutStr("=== RZ/G2L (Memory controller is only channel 1) ===",1);
#elif (RZG2LC == 1)
	PutStr("=== RZ/G2LC (Memory controller is only channel 1) ===",1);
#endif
	readData = *((volatile uint32_t*)0x000000041000000);	//Access Check
	PutStr("Check:0x00_41000000 ... ",0);
	if (CkExtendDdrRamCheck((void*)0x000000041000000))
	{
		PutStr(" Fail!",1);
		PutDdrErrInfo();
		return;
	}
	else
	{
		PutStr(" Pass!",1);
	}
#if (DDR_SIZE_1GB == 0) && (DDR_SIZE_1GB_1PCS == 0) && (DDR_SIZE_512MB_1PCS == 0)
	PutStr("Check:0x00_80000000 ... ",0);
	if (CkExtendDdrRamCheck((void*)0x000000080000000))
	{
		PutStr(" Fail!",1);
		PutDdrErrInfo();
		return;
	}
	else
	{
		PutStr(" Pass!",1);
	}
#if (DDR_SIZE_4GB == 1)
	PutStr("Check:0x00_c0000000 ... ",0);
	if (CkExtendDdrRamCheck((void*)0x0000000c0000000))
	{
		PutStr(" Fail!",1);
		PutDdrErrInfo();
		return;
	}
	else
	{
		PutStr(" Pass!",1);
	}
	PutStr("Check:0x01_00000000 ... ",0);
	if (CkExtendDdrRamCheck((void*)0x000000100000000))
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
#endif
}

static void fill_data_arr1D(uint32_t *dest, uint8_t *src, uint16_t size, uint16_t *offset){
    for (int i = 0; i < size; i++) {
		dest[i] = 	(uint32_t)src[*offset] |
					((uint32_t)src[*offset + 1] << 8)  |
					((uint32_t)src[*offset + 2] << 16) |
					((uint32_t)src[*offset + 3] << 24);
		*offset += 4;
    }
}

static void fill_data_arr2D(uint32_t dest[][2], uint8_t *src, uint16_t size, uint16_t *offset) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 2; j++) {
            dest[i][j] =  (uint32_t)src[*offset] |
                          ((uint32_t)src[*offset + 1] << 8)  |
                          ((uint32_t)src[*offset + 2] << 16) |
                          ((uint32_t)src[*offset + 3] << 24);

            *offset += 4;
        }
    }
}

static void fill_data_char_arr1D(char *dest, char *src, uint8_t size, uint16_t *offset){
    for (int i = 0; i < size; i++) {
		dest[i] = (char)src[*offset];
		*offset += 1;
    }
}

static uint8_t InputFileSize( uint32_t *fileSize )
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

/****************************************************************
	MODULE			: dgDdrLoadParam			*
	FUNCTION		: Load DDR Parameters to RAM		*
	COMMAND			: DDRP			*
	INPUT PARAMETER		: DDRP			*
*****************************************************************/
void dgDdrLoadParam()
{
	uint32_t received = 0U;
	uint32_t fileSize;
	uint16_t offset = 0;
	uint8_t chkInput;
	uint8_t byteData;
	uint8_t ddr_param_buf[DDR_PARAM_FIXED_SIZE];

	chkInput = InputFileSize( &fileSize );
	if (1 != chkInput || fileSize != DDR_PARAM_FIXED_SIZE)
	{
		/* The size of the DDR parameters binary is calculated as DDR_PARAM_FIXED_SIZE = 3776 bytes for RZ/G2L */
		PutStr("Input file size error: DDR parameter file must be 3776 bytes (H'EC0) in size!", 1);
		return;
	}
	PutStr("Please send ! (binary)",1);

	/* Receiving DDR parameters */
	while (received < DDR_PARAM_FIXED_SIZE)
	{
		GetChar(&byteData);
		ddr_param_buf[received++] = byteData;
	}

	/* Load ddr parameters into array local */
	fill_data_arr1D(mc_odt_pins_tbl, ddr_param_buf, 4, &offset);
	fill_data_arr1D(mc_mr1_tbl, ddr_param_buf, 2, &offset);
	fill_data_arr1D(mc_mr2_tbl, ddr_param_buf, 2, &offset);
	fill_data_arr1D(mc_mr5_tbl, ddr_param_buf, 2, &offset);
	fill_data_arr1D(mc_mr6_tbl, ddr_param_buf, 2, &offset);
	fill_data_arr2D(mc_phy_settings_tbl, ddr_param_buf, MC_PHYSET_NUM, &offset);
	fill_data_arr2D(swizzle_mc_tbl, ddr_param_buf, SWIZZLE_MC_NUM, &offset);
	fill_data_arr2D(swizzle_phy_tbl, ddr_param_buf, SIZZLE_PHY_NUM, &offset);
	fill_data_char_arr1D(ddr_an_version, ddr_param_buf, 8, &offset);
	fill_data_arr2D(mc_init_tbl, ddr_param_buf, MC_INIT_NUM, &offset);

	f_ddr_param_initialized = 1;
	PutStr("DDR parameters loaded", 1);
	ddr_setup(OPT_DELAY_RUN);
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
