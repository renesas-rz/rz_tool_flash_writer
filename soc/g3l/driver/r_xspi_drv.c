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
* File Name    : r_xspi_drv.c
* $Revision: 572 $
* Description  : Boot Program XSPI driver source file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : Refer to development project configuration management system
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "xspi_iodefine.h"
#include "r_xspi_drv.h"
#include "timer.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define XSPI_IN 				(0u)
#define XSPI_OUT				(1u)

#define MX25_RDID				(0x00u)
#define MX25_RSTEN				(0x01u)
#define MX25_RST				(0x02u)
#define MX25_WRTEN				(0x03u)
#define MX25_ERASE				(0x04u)
#define MX25_RDSTR				(0x05u)
#define MX25_WRITE				(0x06u)
#define MX25_CHIP_ERASE 		(0x07u)

#define DEVID_ID_MASK			(0x00FFFFFFu)
#define DEVICE_ID_BAD			(0u)
#define DEVICE_ID_ERROR 		(0x00FFFFFFu)

/* Value for xSPI command loop timeout */
#define XSPI_COMMAND_TIMEOUT	(100000u)

#define XSPI_CHANNEL_NUM		(1)
/* get Chaned ID */
#define GET_CH_ID(ch_sec)		(0) 	/* only ch0 support */

/* Power-On Reset values of optimised registers */
#define POR_WRAPCFG_VAL 			(0x00000000UL)
#define POR_COMCFG_VAL				(0x00000000UL)
#define POR_BMCFG_VAL				(0x00000000UL)
#define POR_CMCFG0CSN_VAL			(0x00000000UL)
#define POR_CMCFG1CSN_VAL			(0x00080000UL)
#define POR_LIOCFGCSN_VAL			(0x00070000UL)
#define POR_BMCTL0_VAL				(0x000000FFUL)

/* Reserved bit masks of optimised registers */
#define RES_BITS_WRAPCFG_MASK		(0xE0E0E0E0UL)
#define RES_BITS_COMCFG_MASK		(0xFFFCFFFFUL)
#define RES_BITS_BMCFG_MASK 		(0xFFFE007EUL)
#define RES_BITS_CMCFG0CSN_MASK 	(0x0000FFF0UL)
#define RES_BITS_CMCFG1CSN_MASK 	(0xFFE00000UL)
#define RES_BITS_LIOCFGCSN_MASK 	(0x0000F000UL)

#define XSPI_RESET_WAIT_TIME		(100)				/* wait 100us */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct
{
	uint16_t instruction;
	uint8_t  direction : 3; 	/* Direction */
	uint8_t  latency   : 5; 	/* Latency (cycle) */
	uint8_t  data_size : 4; 	/* Data size (byte) */
	uint8_t  addr_size : 4; 	/* Address size (byte) */
	uint8_t  inst_size : 4; 	/* Instruction size (byte) */
} st_xspi_cmd_t;

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* xSPI base addresses */
static const uint32_t xspi_channel[XSPI_CHANNEL_NUM] =
{
	XSPI_BASE
};

static const st_xspi_cmd_t mx25_cmds[] = {
/* {instruction,   direction,	latency,	 data_size,  addr_size,  cmd_size}*/
	{0x9F00u,		XSPI_IN,	 0u,		   3u,		   0u,		  1u}, /* MX25_RDID */
	{0x6600u,		XSPI_OUT,	 0u,		   0u,		   0u,		  1u}, /* MX25_RSTEN */
	{0x9900u,		XSPI_OUT,	 0u,		   0u,		   0u,		  1u}, /* MX25_RST */
	{0x0600u,		XSPI_OUT,	 0u,		   0u,		   0u,		  1u}, /* Write Enable */
	{0x2000u,		XSPI_OUT,	 0u,		   0u,		   3u,		  1u}, /* Sector Erase */
	{0x0500u,		XSPI_IN,	 0u,		   1u,		   0u,		  1u}, /* Read Status Register-1 */
	{0x0200u,		XSPI_OUT,	 0u,		   1u,		   3u,		  1u}, /* WRITE */
	{0x6000u,		XSPI_OUT,	 0u,		   0u,		   0u,		  1u}  /* Chip Erase */
};

static void xspi_release_module_stop(const uint32_t channel);
static void xspi_set_module_stop(const uint32_t channel);
static void xspi_init_registers(const uint32_t xspi_base, const uint32_t mode);
static d_boot_result_t xspi_prepare(const uint32_t xspi_base);
static d_boot_result_t xspi_reset(const uint32_t xspi_base);
static uint32_t xspi_read_identification(const uint32_t xspi_base);
static d_boot_result_t xspi_single_command(const uint32_t xspi_base, const st_xspi_cmd_info_t * const p_cmd);
static uint32_t xspi_read_status_register(const uint32_t xspi_base);

/***********************************************************************************************************************
* Function Name: r_drv_xspi_init
* Description  : Basic initialialisation of xSPI
* Arguments    : const uint32_t channel_sec - xSPI channel (XSPI_CH0_SEC or XSPI_CH1_SEC)
*                const uint32_t mode_sec    - Operational mode (XSPI_MODE_X1_SEC or XSPI_MODE_X8_SEC)
* Return Value : D_BOOT_OK - Success, D_BOOT_ERR - Failed
***********************************************************************************************************************/
d_boot_result_t r_drv_xspi_init(const uint32_t channel_sec, const uint32_t mode_sec)
{
	d_boot_result_t ret = D_BOOT_ERR;
	uint32_t id = DEVICE_ID_BAD;
	const uint32_t xspi_base = xspi_channel[GET_CH_ID(channel_sec)];

	/* Release xSPI from Module Stop */
	xspi_release_module_stop(channel_sec);
	/* xSPI Init */
	xspi_init_registers(xspi_base, mode_sec);
	/* Initial flash prepare/check */
	ret = xspi_prepare(xspi_base);
	if (D_BOOT_OK == ret)
	{
		/* Resets the flash memory */
		ret = xspi_reset(xspi_base);
	}

	if (D_BOOT_OK == ret)
	{
		/* wait after reset */
		ostm_wait_timer_us(XSPI_RESET_WAIT_TIME);

		/*
		 * Read FLASH memory signature to check we can communicate
		 * successfully (but don't check the ID)
		 */
		id = xspi_read_identification(xspi_base);
		if ((DEVICE_ID_BAD == id) || (DEVICE_ID_ERROR == id))
		{
			/* Failed to read id */
			ret = D_BOOT_ERR;
		}
	}

	return ret;
} /* End of function r_drv_xspi_init() */

/***********************************************************************************************************************
* Function Name: r_drv_xspi_deinit
* Description  : Basic De-initialialisation of xSPI
* Arguments    : const uint32_t channel_sec - xSPI channel (XSPI_CH0_SEC or XSPI_CH1_SEC)
*                const uint32_t mode_sec    - Operational mode (XSPI_MODE_X1_SEC or XSPI_MODE_X8_SEC)
* Return Value : D_BOOT_OK - Success, D_BOOT_ERR - Failed
***********************************************************************************************************************/
d_boot_result_t r_drv_xspi_deinit(const uint32_t channel_sec, const uint32_t mode_sec)
{
	const d_boot_result_t ret = D_BOOT_OK;

	/* Release xSPI from Module Stop */
	xspi_set_module_stop(channel_sec);

	return ret;
} /* End of function r_drv_xspi_deinit() */

/***********************************************************************************************************************
* Function Name: r_drv_xspi_optimise
* Description  : Write optimised values to xSPI if values are valid
* Arguments    : const uint32_t channel_sec - xSPI channel (XSPI_CH0_SEC or XSPI_CH1_SEC)
*                const st_boot_params_t * const p_boot_params - boot paramameters containing potential optimised values
* Return Value : D_BOOT_OK - success; D_BOOT_ERR - invalid value(s)
***********************************************************************************************************************/
d_boot_result_t r_drv_xspi_optimise(const uint32_t channel_sec, const st_boot_params_t * const p_boot_params)
{
	const uint32_t wrapcfg_value   = p_boot_params->m_bus_config_1;
	const uint32_t comcfg_value    = p_boot_params->m_bus_config_2;
	const uint32_t bmcfg_value	   = p_boot_params->m_bus_config_3;
	const uint32_t cmcfg0cs0_value = p_boot_params->m_xspi_cmcfg0cs0;
	const uint32_t cmcfg1cs0_value = p_boot_params->m_xspi_cmcfg1cs0;
	const uint32_t liocfgcs0_value = p_boot_params->m_xspi_liocfgcs0;
	const uint32_t xspi_base = xspi_channel[GET_CH_ID(channel_sec)];
	d_boot_result_t ret = D_BOOT_OK;

	/* If optimisation values are present then cmcfg0cs0_value must be non zero
		as it contains memory mapping and enable data*/
	if (0u != cmcfg0cs0_value)
	{
		/* Check for reserved bits being inappropriately set in WRAPCFG */
		if ((RES_BITS_WRAPCFG_MASK & wrapcfg_value) != 0u)
		{
			ret = D_BOOT_ERR;
		}

		/* Check for reserved bits being inappropriately set in COMCFG */
		if ((RES_BITS_COMCFG_MASK & comcfg_value) != 0u)
		{
			ret = D_BOOT_ERR;
		}

		/* Check for reserved bits being inappropriately set in BMCFG */
		if ((RES_BITS_BMCFG_MASK & bmcfg_value) != 0u)
		{
			ret = D_BOOT_ERR;
		}

		/* Check for reserved bits being inappropriately set in CMCFG0CS0 */
		if ((RES_BITS_CMCFG0CSN_MASK & cmcfg0cs0_value) != 0u)
		{
			ret = D_BOOT_ERR;
		}

		/* Check for reserved bits being inappropriately set in CMCFG1CS0*/
		if ((RES_BITS_CMCFG1CSN_MASK & cmcfg1cs0_value) != 0u)
		{
			ret = D_BOOT_ERR;
		}

		/* Check for reserved bits being inappropriately set in LIOCFGCS0 */
		if ((RES_BITS_LIOCFGCSN_MASK & liocfgcs0_value) != 0u)
		{
			ret = D_BOOT_ERR;
		}

		/* Confirm that all value checks passed before writing optimised values */
		if (D_BOOT_OK == ret)
		{
			/* Optimised values validated. Now write them */
			*XSPI_WRAPCFG(xspi_base)   = wrapcfg_value;
			*XSPI_COMCFG(xspi_base)    = comcfg_value;
			*XSPI_BMCFG(xspi_base)	   = bmcfg_value;
			*XSPI_CMCFG0CS0(xspi_base) = cmcfg0cs0_value;
			*XSPI_CMCFG1CS0(xspi_base) = cmcfg1cs0_value;
			*XSPI_LIOCFGCS0(xspi_base) = liocfgcs0_value;
		}
	}

	return ret;
} /* End of function r_drv_xspi_optimise() */

/***********************************************************************************************************************
* Function Name: r_drv_xspi_restore_default
* Description  : Restore power up default BSC settings
* Arguments    : const uint32_t channel_sec - xSPI channel (XSPI_CH0_SEC or XSPI_CH1_SEC)
* Return Value : D_BOOT_OK - success; D_BOOT_ERR - invalid channel
***********************************************************************************************************************/
d_boot_result_t r_drv_xspi_restore_default(const uint32_t channel_sec)
{
	const uint32_t xspi_base = xspi_channel[GET_CH_ID(channel_sec)];

	*XSPI_WRAPCFG(xspi_base)   = POR_WRAPCFG_VAL;
	*XSPI_COMCFG(xspi_base)    = POR_COMCFG_VAL;
	*XSPI_BMCFG(xspi_base)	   = POR_BMCFG_VAL;
	*XSPI_CMCFG0CS0(xspi_base) = POR_CMCFG0CSN_VAL;
	*XSPI_CMCFG1CS0(xspi_base) = POR_CMCFG1CSN_VAL;
	*XSPI_LIOCFGCS0(xspi_base) = POR_LIOCFGCSN_VAL;
	*XSPI_BMCTL0(xspi_base)    = POR_BMCTL0_VAL;

	return D_BOOT_OK;
} /* End of function r_drv_xspi_restore_default() */

/**********************************************************************************************************************
 * Function Name: R_DRV_XSPI_Erase
* Description   : 
 * Arguments    : uint32_t xspi_base - base address of xSPI controller
 * Return Value : Device id (will be DEVICE_ID_BAD (0) or DEVICE_ID_ERROR (0x00FFFFFF) if an error occurs)
***********************************************************************************************************************/
uint32_t R_DRV_XSPI_Erase(const uint32_t channel_sec, const uintptr_t dest_addr, uint32_t byte_count)
{
	volatile int32_t ret = D_BOOT_ERR;
	uint32_t xspi_base = xspi_channel[GET_CH_ID(channel_sec)];

	volatile uint32_t status = 0xFFFFFFFF;

	st_xspi_cmd_info_t wrten_cmd = {MX25_WRTEN, 0, 0};
	st_xspi_cmd_info_t erase_cmd = {MX25_ERASE, 0, 0};

	/* by 4096byte */
	uint32_t count = (byte_count >> 12) + 1;

	for (int i = 0; i < count; i++)
	{
		erase_cmd.addr = dest_addr + (i * 0x1000);
		// Write Enable
		ret = xspi_single_command(xspi_base, &wrten_cmd);

		/* wait 15ms */
		ostm_wait_timer_ms(15);

		// Erase
		ret = xspi_single_command(xspi_base, &erase_cmd);

		do
   		{
	   		status = xspi_read_status_register(xspi_base);
		}while (0< (status & 0x01));
	}

	return ret;
} /* End of function xspi_read_identification() */

uint32_t R_DRV_XSPI_ChipErase(const uint32_t channel_sec)
{
	volatile int32_t ret = D_BOOT_ERR;
	uint32_t xspi_base = xspi_channel[GET_CH_ID(channel_sec)];

	volatile uint32_t status = 0xFFFFFFFF;

	st_xspi_cmd_info_t wrten_cmd = {MX25_WRTEN, 0, 0};
	st_xspi_cmd_info_t erase_cmd = {MX25_CHIP_ERASE, 0, 0};

	// Write Enable
	ret = xspi_single_command(xspi_base, &wrten_cmd);

	/* wait 15ms */
	ostm_wait_timer_ms(15);

	// Erase
	ret = xspi_single_command(xspi_base, &erase_cmd);

	do
	{
		status = xspi_read_status_register(xspi_base);
	} while (0< (status & 0x01));

	return ret;
} /* End of function xspi_read_identification() */

/**********************************************************************************************************************
 * Function Name: R_DRV_XSPI_Write
 * Description  : 
 * Arguments    : uint32_t xspi_base - base address of xSPI controller
 * Return Value : Device id (will be DEVICE_ID_BAD (0) or DEVICE_ID_ERROR (0x00FFFFFF) if an error occurs)
***********************************************************************************************************************/
uint32_t R_DRV_XSPI_Write(const uint32_t channel_sec, const uintptr_t dest_addr, uintptr_t data, uint32_t byte_count)
{
	volatile int32_t ret = D_BOOT_ERR;
	uint32_t xspi_base = xspi_channel[GET_CH_ID(channel_sec)];

	volatile uint32_t status = 0xFFFFFFFF;

	st_xspi_cmd_info_t wrten_cmd = {MX25_WRTEN, 0, 0};

	int32_t count = byte_count/4;

	uint32_t* dst = (uint32_t*)(dest_addr + 0x20000000);
	uint32_t* src = (uint32_t*)data;

	for (int i = 0; i < count; i++) 
	{
		// Write Enable
		ret = xspi_single_command(xspi_base, &wrten_cmd);

		// memory area access enable Read/Write
		*XSPI_BMCTL0(xspi_base) = (0x03u << XSPI_BMCTL0_CS0ACC);

		*dst = *src;
		dst++;
		src++;
		do
		{
		   status = xspi_read_status_register(xspi_base);
		}while(0< (status & 0x01));
	}

	return ret;
} /* End of function xspi_read_identification() */

void R_DRV_XSPI_ReadId(const uint32_t channel_sec, uint32_t *readData)
{
	uint32_t id = DEVICE_ID_BAD;
	const uint32_t xspi_base = xspi_channel[GET_CH_ID(channel_sec)];

	id = xspi_read_identification(xspi_base);
	*readData = id;
}


/***********************************************************************************************************************
* Function Name: xspi_release_module_stop
* Description  : Release xSPI from Module Stop and reset it
* Arguments    : const uint32_t channel_sec - xSPI channel (XSPI_CH0_SEC or XSPI_CH1_SEC)
* Return Value : N/A
***********************************************************************************************************************/
static void xspi_release_module_stop(const uint32_t channel_sec)
{
	/* Do module stop with boot main */
	/* Release MSTOP for XSPI0 */
	/* *CPG_BUS_5_MSTOP = (CPG_MSTOP_XSPI0_WEN | CPG_MSTOP_XSPI0_ON);*/
} /* End of function xspi_release_module_stop() */

/***********************************************************************************************************************
* Function Name: xspi_set_module_stop
* Description  : Set xSPI from Module Stop and reset it
* Arguments    : const uint32_t channel_sec - xSPI channel (XSPI_CH0_SEC or XSPI_CH1_SEC)
* Return Value : N/A
***********************************************************************************************************************/
static void xspi_set_module_stop(const uint32_t channel_sec)
{
	/* Do module stop with boot main */
	/* Set MSTOP for XSPI0 */
	/* *CPG_BUS_5_MSTOP = (CPG_MSTOP_XSPI0_WEN | CPG_MSTOP_XSPI0_OFF);*/
} /* End of function xspi_set_module_stop() */

/***********************************************************************************************************************
* Function Name: xspi_init_registers
* Description  : Initialise xSPI controller registers for memory mapped mode
* Arguments    : uint32_t xspi_base - base address of xSPI controller
*                uint32_t mode_sec  - device mode (XSPI_MODE_X1_SEC or XSPI_MODE_X8_SEC)
* Return Value :  N/A
***********************************************************************************************************************/
static void xspi_init_registers(const uint32_t xspi_base, const uint32_t mode_sec)
{
	uint32_t reg_temp;
	
	switch (mode_sec)
	{
		case XSPI_MODE_X1_SEC:
		{
			/* Set SPI mode - sample data at falling edge, drive clock at falling edge, 1S-1S-1S */
			reg_temp =	*XSPI_LIOCFGCS0(xspi_base) & ~(XSPI_LIOCFGCS_PRTMD_MSK);
			reg_temp |= XSPI_LIOCFGCS_PRTMD_1S_1S_1S;
			*XSPI_LIOCFGCS0(xspi_base) = reg_temp;
			/* Set memory mapping mode */
			*XSPI_CMCFG0CS0(xspi_base) = ((0x00u << XSPI_CMCFG0CS_ADDRPCD)
										| (0x00u << XSPI_CMCFG0CS_ADDRPEN)
										| (0x00u << XSPI_CMCFG0CS_ARYAM)
										| (0x00u << XSPI_CMCFG0CS_WPBST)
										| (0x02u << XSPI_CMCFG0CS_ADDSIZE)
										| (0x00u << XSPI_CMCFG0CS_FFMT));

			/* 0 latency, 0x0300 read command */
			*XSPI_CMCFG1CS0(xspi_base) = ((0x00u << XSPI_CMCFG1CS_RDLATE)
										| (0x0300u << XSPI_CMCFG1CS_RDCMD));

			/* 0 latency, 0x0200 write command */
			*XSPI_CMCFG2CS0(xspi_base) = (0x00u << XSPI_CMCFG1CS_WRLATE)
									  | (0x0200u << XSPI_CMCFG1CS_WRCMD);

			/* Enable read access to CS0 for selected channel memory areas */
//			  *XSPI_BMCTL0(xspi_base) = ((0x01u << XSPI_BMCTL0_CS0ACC)
//									  |  (0x00 << XSPI_BMCTL0_CS1ACC)
//									  |  (0x00 << XSPI_BMCTL0_CH1CS0ACC)
//									  |  (0x00 << XSPI_BMCTL0_CH1CS1ACC));
			/* Enable read access to CS0 for selected channel memory areas */ /* Read/Write Enable */
			*XSPI_BMCTL0(xspi_base) = (0x03u << XSPI_BMCTL0_CS0ACC);
			/* Enable prefetch */
			*XSPI_BMCFG(xspi_base) = (0x01u << XSPI_BMCFG_PREEN)
								  | (0x00u << XSPI_BMCFG_MWRSIZE)
								  | (0x01u << XSPI_BMCFG_WRMD);

			/* WRAPCFG: use default values */
			/* COMCFG:	use default values */
			/* BMCFG:	use default values */
			/* CSSCTL:	use default values */
			break;
		}

		case XSPI_MODE_X8_SEC:
		{
			*XSPI_WRAPCFG(xspi_base)	= (0x1Fu << XSPI_WRAPCFG_DSSFTCS0);
		
			/* Set SPI mode - 8D-8D-8D */
			reg_temp =	*XSPI_LIOCFGCS0(xspi_base) & ~(XSPI_LIOCFGCS_PRTMD_MSK | XSPI_LIOCFGCS_LATEMD_MSK);
			reg_temp |= (XSPI_LIOCFGCS_PRTMD_8D_8D_8D | (0x01u << XSPI_LIOCFGCS_LATEMD));
			*XSPI_LIOCFGCS0(xspi_base) = reg_temp;

			/* Set memory mapping mode */
			*XSPI_CMCFG0CS0(xspi_base) = ((0x00u << XSPI_CMCFG0CS_ADDRPCD)
										| (0x00u << XSPI_CMCFG0CS_ADDRPEN)
										| (0x00u << XSPI_CMCFG0CS_ARYAM)
										| (0x00u << XSPI_CMCFG0CS_WPBST)
										| (0x03u << XSPI_CMCFG0CS_ADDSIZE)
										| (0x02u << XSPI_CMCFG0CS_FFMT));

			/* 10 cycle latency, 0xA000 read command */
			*XSPI_CMCFG1CS0(xspi_base) = ((0x0Au << XSPI_CMCFG1CS_RDLATE)
										| (0xA000u << XSPI_CMCFG1CS_RDCMD));

			/* Enable read access to CS0 for selected channel memory areas */
			*XSPI_BMCTL0(xspi_base) = ((0x01u << XSPI_BMCTL0_CS0ACC)
									|  (0x00 << XSPI_BMCTL0_CS1ACC)
									|  (0x00 << XSPI_BMCTL0_CH1CS0ACC)
									|  (0x00 << XSPI_BMCTL0_CH1CS1ACC));

			/* COMCFG:	use default values */
			/* BMCFG:	use default values */
			/* CSSCTL:	use default values */
			break;
		}

		default:
			/* Error */
			break;
	}

} /* End of function xspi_init_registers() */

/***********************************************************************************************************************
* Function Name: xspi_prepare
* Description  : Prepare xSPI module for commands and check command status
* Arguments    : uint32_t xspi_base - base address of xSPI controller
* Return Value : D_BOOT_OK if success, D_BOOT_ERR if error
***********************************************************************************************************************/
static d_boot_result_t xspi_prepare(const uint32_t xspi_base)
{
	/* Check if transaction has already been requested. If so return error */
	if (0u != ((*XSPI_CDCTL0(xspi_base)) & XSPI_CDCTL0_TRREQ_MSK))
	{
		return D_BOOT_ERR;
	}

	*XSPI_INTC(xspi_base)	 = ((*XSPI_INTC(xspi_base)) | (XSPI_INTC_CMDCMPC_MSK));
	*XSPI_CDTBUF0(xspi_base) = ((*XSPI_CDTBUF0(xspi_base)) &
									(~((XSPI_CDTBUF_ADDSIZE_MSK) | (XSPI_CDTBUF_CMDSIZE_MSK))));

	return D_BOOT_OK;
} /* End of function xspi_prepare() */

/***********************************************************************************************************************
* Function Name: xspi_reset
* Description  : Reset the external xSPI Flash device
* Arguments    : uint32_t xspi_base - base address of xSPI controller
* Return Value : D_BOOT_OK if Success, D_BOOT_ERR if timeout
***********************************************************************************************************************/
static d_boot_result_t xspi_reset(const uint32_t xspi_base)
{
	d_boot_result_t ret = D_BOOT_ERR;
	st_xspi_cmd_info_t m_cmd_info = {0};

	m_cmd_info.cmd_idx = MX25_RSTEN;
	ret = xspi_single_command(xspi_base, &m_cmd_info);
	if (D_BOOT_OK == ret)
	{
		m_cmd_info.cmd_idx = MX25_RST;
		ret = xspi_single_command(xspi_base, &m_cmd_info);
	}

	return ret;
} /* End of function xspi_reset() */

/***********************************************************************************************************************
* Function Name: xspi_read_identification
* Description  : Read xSPI device id
* Arguments    : uint32_t xspi_base - base address of xSPI controller
* Return Value : Device id (will be DEVICE_ID_BAD (0) or DEVICE_ID_ERROR (0x00FFFFFF) if an error occurs)
***********************************************************************************************************************/
static uint32_t xspi_read_identification(const uint32_t xspi_base)
{
	uint32_t device_id = DEVICE_ID_BAD;
	uint32_t prev_id = DEVICE_ID_BAD;
	uint32_t count = 1000;
	st_xspi_cmd_info_t m_cmd_info = {0};

	m_cmd_info.cmd_idx = MX25_RDID;

	while (count)
	{
		if (D_BOOT_OK == xspi_single_command(xspi_base, &m_cmd_info))
		{
			/* Command success */
			device_id = (*XSPI_CDD0BUF0(xspi_base)) & DEVID_ID_MASK;
			if ( (DEVICE_ID_BAD != device_id) && (DEVICE_ID_ERROR != device_id) && (prev_id == device_id))
			{
				/* Hardware ID is valid and has been repeated on two consecutive reads
					so exit the while loop and then function */
				break;
			}

			prev_id = device_id;
		}
		/* Allow retry of Id read in case Flash device has not had enough time to start-up*/
		count--;
	}

	return device_id;
} /* End of function xspi_read_identification() */



/***********************************************************************************************************************
* Function Name: xspi_read_status_register
* Description  : Read xSPI device id
* Arguments    : uint32_t xspi_base - base address of xSPI controller
* Return Value : Device id (will be DEVICE_ID_BAD (0) or DEVICE_ID_ERROR (0x00FFFFFF) if an error occurs)
***********************************************************************************************************************/
static uint32_t xspi_read_status_register(const uint32_t xspi_base)
{
	volatile uint32_t status = 0xFFFFFFFF;

	st_xspi_cmd_info_t rdstr_cmd = {0};
	rdstr_cmd.cmd_idx = MX25_RDSTR;

	if (D_BOOT_OK == xspi_single_command(xspi_base, &rdstr_cmd))
	{
		/* Command success */
		status = *XSPI_CDD0BUF0(xspi_base);
	}
	/* Allow retry of Id read in case Flash device has not had enough time to start-up*/

	return status;
} /* End of function xspi_read_status_register() */

/***********************************************************************************************************************
* Function Name: xspi_single_command
* Description  : Execute xSPI device command
* Arguments    : uint32_t xspi_base - base address of xSPI controller
*                st_xspi_cmd_info_t* p_cmd_info - command information
* Return Value : D_BOOT_OK if success, D_BOOT_ERR if error
***********************************************************************************************************************/
static d_boot_result_t xspi_single_command(const uint32_t xspi_base, const st_xspi_cmd_info_t * const p_cmd_info)
{
	uint32_t timeout;

	*XSPI_CDCTL0(xspi_base)  = (*XSPI_CDCTL0(xspi_base)) & (~(XSPI_CDCTL0_TRREQ_MSK));

	*XSPI_CDTBUF0(xspi_base) = (((uint32_t)mx25_cmds[p_cmd_info->cmd_idx].instruction) << XSPI_CDTBUF_CMD)
							| (((uint32_t)mx25_cmds[p_cmd_info->cmd_idx].direction) << XSPI_CDTBUF_TRTYPE)
							| (((uint32_t)mx25_cmds[p_cmd_info->cmd_idx].latency)	<< XSPI_CDTBUF_LATE)
							| (((uint32_t)mx25_cmds[p_cmd_info->cmd_idx].data_size) << XSPI_CDTBUF_DATASIZE)
							| (((uint32_t)mx25_cmds[p_cmd_info->cmd_idx].addr_size) << XSPI_CDTBUF_ADDSIZE)
							| (((uint32_t)mx25_cmds[p_cmd_info->cmd_idx].inst_size) << XSPI_CDTBUF_CMDSIZE);

	*XSPI_CDABUF0(xspi_base)  = p_cmd_info->addr;
	*XSPI_CDD0BUF0(xspi_base) = p_cmd_info->data;

	*XSPI_CDCTL0(xspi_base) = (*XSPI_CDCTL0(xspi_base)) | XSPI_CDCTL0_TRREQ_MSK;

	timeout = XSPI_COMMAND_TIMEOUT;
	/* Wait for command to complete */
	while ((0u == ((*XSPI_INTS(xspi_base)) & XSPI_INTS_CMDCMP_MSK)) && (timeout > 0u))
	{
		timeout--;
	}

	*XSPI_INTC(xspi_base) = ((*XSPI_INTC(xspi_base)) | (XSPI_INTC_CMDCMPC_MSK));

	return (0u == timeout) ? D_BOOT_ERR : D_BOOT_OK;
} /* End of function xspi_single_command() */

/* End of File */
