/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_xspi_drv.h
* $Revision: 489 $
* Description  : Boot Program XSPI driver header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : Refer to development project configuration management system
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef R_XSPI_DRV_H
#define R_XSPI_DRV_H

#define CACHE_FLG_ENABLE			(0x00000001)
#define CACHE_FLG_DISABLE			(0x00000000)

#define BOOT_PARAM_FLG_RESTORE		(0x22360679)

typedef enum
{
	D_BOOT_OK  =					0x33333333, 		/* Successful operation */
	D_BOOT_ERR =					0xAAAAAAAA, 		/* Fail 				*/
	D_BOOT_S_BOOT_ERR = 			0x44444444, 		/* R_SB_SecureBoot result error 	   */
	D_BOOT_M_BOOT_ERR = 			0xBBBBBBBB			/* R_CIP_DRV_MeasuredBoot result error */
} d_boot_result_t;

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Definitions for XSPI Channel */
typedef enum e_xspi_channel_sec
{
	/* XSPI Channel number */
	XSPI_CH0_SEC  = 0x00000028,
	XSPI_CH1_SEC  = 0x00019fd7,

	/* The inverted values */
	XSPI_CH0_SEC_INV  = 0xffffffd7,
	XSPI_CH1_SEC_INV  = 0xfffe6028,
} e_xspi_channel_sec_t;

/* Definitions for XSPI mode */
typedef enum e_xspi_modes_sec
{
	/* XSPI Operation mode */
	XSPI_MODE_X1_SEC  = 0x007e61c3,
	XSPI_MODE_X8_SEC  = 0x07866ddc,

	/* The inverted values */
	XSPI_MODE_X1_SEC_INV  = 0xff819e3c,
	XSPI_MODE_X8_SEC_INV  = 0xf8799223,
} e_xspi_modes_sec_t;

typedef struct
{
	uint32_t	m_cache_flag;		/* @ 0x0000_0000 */
	uint32_t	m_bus_config_1; 	/* @ 0x0000_0004 BSC: CS0BCR_V, XSPI: WRAPCFG_V */
	uint32_t	m_bus_config_2; 	/* @ 0x0000_0008 BSC: CS0WCR_V, XSPI: COMCFG_V */
	uint32_t	m_bus_config_3; 	/* @ 0x0000_000C BSC: not used, XSPI: BMCFG_V */
	uint32_t	m_bus_restore;		/* @ 0x0000_0010 */
	uint32_t	m_loader_addr;		/* @ 0x0000_0014 */
	uint32_t	m_loader_size;		/* @ 0x0000_0018 */
	uint32_t	m_dest_addr;		/* @ 0x0000_001C */
	uint32_t	m_xspi_cmcfg0cs0;	/* @ 0x0000_0020 These parameters are XSPI specific */
	uint32_t	m_xspi_cmcfg1cs0;	/* @ 0x0000_0024 */
	uint32_t	m_xspi_cmcfg2cs0;	/* @ 0x0000_0028 */
	uint32_t	m_xspi_liocfgcs0;	/* @ 0x0000_002C */
	uint32_t	m_xspi_cmcfg0cs1;	/* @ 0x0000_0030 */
	uint32_t	m_xspi_cmcfg1cs1;	/* @ 0x0000_0034 */
	uint32_t	m_xspi_cmcfg2cs1;	/* @ 0x0000_0038 */
	uint32_t	m_xspi_liocfgcs1;	/* @ 0x0000_003C */
	uint8_t 	m_dummy_2[0x08];	/* @ 0x0000_0040-44 */
	uint32_t	m_checksum; 		/* @ 0x0000_0048 */
} st_boot_params_t;

/* Definitions of Boot Parameter Cache enable */
typedef enum e_bp_cache_enable_sec
{
	/* Inverse pair */
	CACHE_ENABLE_SEC  = 0x1be1b561,
	CACHE_DISABLE_SEC = 0xe41e4a9e,
} e_bp_cache_enable_sec_t;

typedef struct
{
	uint8_t  cmd_idx;
	uint32_t addr;
	uint32_t data;
} st_xspi_cmd_info_t;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
extern d_boot_result_t r_drv_xspi_init(const uint32_t channel_sec, const uint32_t mode_sec);
extern d_boot_result_t r_drv_xspi_deinit(const uint32_t channel_sec, const uint32_t mode_sec);
extern d_boot_result_t r_drv_xspi_optimise(const uint32_t channel_sec, const st_boot_params_t * const p_boot_params);
extern d_boot_result_t r_drv_xspi_restore_default(const uint32_t channel);

extern uint32_t R_DRV_XSPI_Erase(const uint32_t channel_sec, const uintptr_t dest_addr, uint32_t byte_count);
extern uint32_t R_DRV_XSPI_Write(const uint32_t channel_sec, const uintptr_t dest_addr, uintptr_t src, uint32_t byte_count);
extern void R_DRV_XSPI_ReadId(const uint32_t channel_sec, uint32_t *readData);
extern uint32_t R_DRV_XSPI_ChipErase(const uint32_t channel_sec);
#endif /* R_XSPI_DRV_H */

/* End of File */
