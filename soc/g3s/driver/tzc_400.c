/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <rz_soc_def.h>

/*** Registers for ACPU ***/
#define TZC_GATE_KEEP_SRAM_A0   ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x008ul))    /* Gate Keeper register */
#define TZC_SPECUL_CTL_SRAM_A0  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x00Cul))    /* Speculation control register */
#define TZC_RGN_ATTR_SRAM_A0    ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x110ul))    /* Region attributes register */
#define TZC_RGN_ID_ACC_SRAM_A0  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x114ul))    /* Region ID access register */

#define TZC_GATE_KEEP_SRAM_A1   ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x008ul))    /* Gate Keeper register */
#define TZC_SPECUL_CTL_SRAM_A1  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x00Cul))    /* Speculation control register */
#define TZC_RGN_ATTR_SRAM_A1    ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x110ul))    /* Region attributes register */
#define TZC_RGN_ID_ACC_SRAM_A1  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x114ul))    /* Region ID access register */

#define TZC_GATE_KEEP_SRAM_A2   ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x008ul))    /* Gate Keeper register */
#define TZC_SPECUL_CTL_SRAM_A2  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x00Cul))    /* Speculation control register */
#define TZC_RGN_ATTR_SRAM_A2    ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x110ul))    /* Region attributes register */
#define TZC_RGN_ID_ACC_SRAM_A2  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_A0_BASE + 0x114ul))    /* Region ID access register */

/*** Registers for MCPU ***/
#define TZC_GATE_KEEP_SRAM_M0   ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x008ul))    /* Gate Keeper register */
#define TZC_SPECUL_CTL_SRAM_M0  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x00Cul))    /* Speculation control register */
#define TZC_RGN_ATTR_SRAM_M0    ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x110ul))    /* Region attributes register */
#define TZC_RGN_ID_ACC_SRAM_M0  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x114ul))    /* Region ID access register */

#define TZC_GATE_KEEP_SRAM_M1   ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x008ul))    /* Gate Keeper register */
#define TZC_SPECUL_CTL_SRAM_M1  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x00Cul))    /* Speculation control register */
#define TZC_RGN_ATTR_SRAM_M1    ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x110ul))    /* Region attributes register */
#define TZC_RGN_ID_ACC_SRAM_M1  ((volatile uint32_t *)(RZG3S_TZC400_SRAM_M0_BASE + 0x114ul))    /* Region ID access register */

/*** Registers for xSPI ***/
#define TZC_GATE_KEEP_SPI       ((volatile uint32_t *)(RZG3S_TZC400_xSPI_BASE     + 0x008ul))    /* Gate Keeper register */
#define TZC_SPECUL_CTL_SPI      ((volatile uint32_t *)(RZG3S_TZC400_xSPI_BASE     + 0x00Cul))    /* Speculation control register */
#define TZC_RGN_ATTR_SPI        ((volatile uint32_t *)(RZG3S_TZC400_xSPI_BASE     + 0x110ul))    /* Region attributes register */
#define TZC_RGN_ID_ACC_SPI      ((volatile uint32_t *)(RZG3S_TZC400_xSPI_BASE     + 0x114ul))    /* Region ID access register */

/*** Registers for DDR ***/
#define TZC_GATE_KEEP_DDR       ((volatile uint32_t *)(RZG3S_TZC400_DDR_BASE     + 0x008ul))    /* Gate Keeper register */
#define TZC_SPECUL_CTL_DDR      ((volatile uint32_t *)(RZG3S_TZC400_DDR_BASE     + 0x00Cul))    /* Speculation control register */
#define TZC_RGN_ATTR_DDR        ((volatile uint32_t *)(RZG3S_TZC400_DDR_BASE     + 0x110ul))    /* Region attributes register */
#define TZC_RGN_ID_ACC_DDR      ((volatile uint32_t *)(RZG3S_TZC400_DDR_BASE     + 0x114ul))    /* Region ID access register */

/*** Mask/Setting bit patter for registers ***/
#define TZC_GATE_KEEP_SET_BIT           (0x0000000Ful)  /* Setting bit pattern */
#define TZC_SPECUL_CTL_SET_BIT          (0x00000003ul)  /* Setting bit pattern */
#define TZC_RGN_ATTR_MSK                (0x0FFFFFFFul)  /* Mask bit pattern */
#define TZC_RGN_ID_ACC_SET_BIT          (0x000F000Ful)  /* Setting bit pattern */

#define TZC_GATE_KEEP_OPEN_ALLFLT       (0x0000000Ful)  /* Open all filter unit */
#define TZC_SPECUL_DIS_PREFETCH         (0x00000003ul)  /* Disable pre-fetch */
#define TZC_RGN_ATTR_EN_ALLFLT          (0x0000000Ful)  /* Enable all filter unit */
#define TZC_RGN_ID_ACC_EN_RDWR_NSAID0_1 (0x000F000Ful)  /* Enable NSAIDW<x>: 0, 1, NSAIDR<x>: 0, 1   */

/**********************************************************************************************************************
 * Function Name: init_tzc_400_xspi
 * Description  : Initialize TAC-400 for xSPI.
 * Arguments    : none.
 * Return Value : none.
 *********************************************************************************************************************/
void init_tzc_400_xspi(void)
{
	/*** Initialize xSPI ***/
	*TZC_RGN_ATTR_SPI	= TZC_RGN_ATTR_EN_ALLFLT;

	*TZC_RGN_ID_ACC_SPI = TZC_RGN_ID_ACC_EN_RDWR_NSAID0_1;

	*TZC_GATE_KEEP_SPI	= TZC_GATE_KEEP_OPEN_ALLFLT;

	*TZC_SPECUL_CTL_SPI = TZC_SPECUL_DIS_PREFETCH;
}
/**********************************************************************************************************************
 * End of function init_tzc_400_xspi
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: init_tzc_400_ddr
 * Description  : Initialize TAC-400 for DDR.
 * Arguments    : none.
 * Return Value : none.
 *********************************************************************************************************************/
void init_tzc_400_ddr(void)
{
	/*** Initialize DDR ***/
	*TZC_RGN_ATTR_DDR	= TZC_RGN_ATTR_EN_ALLFLT;

	*TZC_RGN_ID_ACC_DDR = TZC_RGN_ID_ACC_EN_RDWR_NSAID0_1;

	*TZC_GATE_KEEP_DDR	= TZC_GATE_KEEP_OPEN_ALLFLT;

	*TZC_SPECUL_CTL_DDR = TZC_SPECUL_DIS_PREFETCH;;
}
