/*
 * Copyright (c) 2022, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __CPG_REGS_H__
#define __CPG_REGS_H__

#include <rz_soc_def.h>				/* Get the CPG base address */

#define	CPG_PLLCM33_MON				(CPG_BASE + 0x010)	/* PLLCM33 monitor register */

#define	CPG_PLLCLN_STBY				(CPG_BASE + 0x020)	/* PLLCLN standby control register */
#define	CPG_PLLCLN_MON				(CPG_BASE + 0x030)	/* PLLCLN monitor register */

#define	CPG_PLLDTY_STBY				(CPG_BASE + 0x040)	/* PLLDTY standby control register */
#define	CPG_PLLDTY_MON				(CPG_BASE + 0x050)	/* PLLDTY monitor register */

#define	CPG_PLLCA55_STBY			(CPG_BASE + 0x060)	/* PLLCA55 standby control register */
#define	CPG_PLLCA55_CLK1			(CPG_BASE + 0x064)	/* PLLCA55 output clock setting register 1 */
#define	CPG_PLLCA55_CLK2			(CPG_BASE + 0x068)	/* PLLCA55 output clock setting register 2 */
#define	CPG_PLLCA55_MON				(CPG_BASE + 0x070)	/* PLLCA55 monitor register */

#define	CPG_PLLVDO_STBY				(CPG_BASE + 0x080)	/* PLLVDO standby control register */
#define	CPG_PLLVDO_MON				(CPG_BASE + 0x090)	/* PLLVDO monitor register */

#define	CPG_PLLETH_STBY				(CPG_BASE + 0x0A0)	/* PLLETH standby control register */
#define	CPG_PLLETH_MON				(CPG_BASE + 0x0B0)	/* PLLETH monitor register */

#define	CPG_PLLDSI0_STBY			(CPG_BASE + 0x0C0)	/* PLLDSI0 standby control register */
#define	CPG_PLLDSI0_CLK1			(CPG_BASE + 0x0C4)	/* PLLDSI0 output clock setting register 1 */
#define	CPG_PLLDSI0_CLK2			(CPG_BASE + 0x0C8)	/* PLLDSI0 output clock setting register 2 */
#define	CPG_PLLDSI0_MON				(CPG_BASE + 0x0D0)	/* PLLDSI0 monitor register */

#define	CPG_PLLDDR0_STBY			(CPG_BASE + 0x0E0)	/* PLLDDR0 standby control register */
#define	CPG_PLLDDR0_MON				(CPG_BASE + 0x0F0)	/* PLLDDR0 monitor register*/

#define	CPG_PLLDSI1_STBY			(CPG_BASE + 0x160)	/* PLLDSI0 standby control register */
#define	CPG_PLLDSI1_CLK1			(CPG_BASE + 0x164)	/* PLLDSI0 output clock setting register 1 */
#define	CPG_PLLDSI1_CLK2			(CPG_BASE + 0x168)	/* PLLDSI0 output clock setting register 2 */
#define	CPG_PLLDSI1_MON				(CPG_BASE + 0x170)	/* PLLDSI0 monitor register */


#define	CCLMA0_CTL					(CPG_BASE + 0x200)	/* CLMA0 control register */
#define	CCLMA1_CTL					(CPG_BASE + 0x204)	/* CLMA1 control register */
#define	CCLMA2_CTL					(CPG_BASE + 0x208)	/* CLMA2 control register */
#define	CCLMA3_CTL					(CPG_BASE + 0x20C)	/* CLMA3 control register */
#define	CCLMA4_CTL					(CPG_BASE + 0x210)	/* CLMA4 control register */
#define	CCLMA5_CTL					(CPG_BASE + 0x214)	/* CLMA5 control register */
#define	CCLMA6_CTL					(CPG_BASE + 0x218)	/* CLMA6 control register */
#define	CCLMA7_CTL					(CPG_BASE + 0x21C)	/* CLMA7 control register */
#define	CCLMA8_CTL					(CPG_BASE + 0x220)	/* CLMA8 control register */
#define	CCLMA9_CTL					(CPG_BASE + 0x224)	/* CLMA9 control register */
#define	CCLMA10_CTL					(CPG_BASE + 0x228)	/* CLMA10 control register */
#define	CCLMA11_CTL					(CPG_BASE + 0x22C)	/* CLMA11 control register */
#define	CCLMA12_CTL					(CPG_BASE + 0x230)	/* CLMA12 control register */
#define	CCLMA13_CTL					(CPG_BASE + 0x234)	/* CLMA13 control register */
#define	CCLMA14_CTL					(CPG_BASE + 0x238)	/* CLMA14 control register */

#define	CCLMA_MON					(CPG_BASE + 0x280)	/* CLMA monitor register */

#define	CPG_SSEL0					(CPG_BASE + 0x300)	/* Static Mux control */
#define	CPG_SSEL1					(CPG_BASE + 0x304)	/* Static Mux control */

#define	CPG_CDDIV0					(CPG_BASE + 0x400)	/* Dynamic Gear control(Counter type) */
#define	CPG_CDDIV1					(CPG_BASE + 0x404)	/* Dynamic Gear control(Counter type) */
#define	CPG_CDDIV2					(CPG_BASE + 0x408)	/* Dynamic Gear control(Counter type) */
#define	CPG_CDDIV3					(CPG_BASE + 0x40c)	/* Dynamic Gear control(Counter type) */
#define	CPG_CDDIV4					(CPG_BASE + 0x410)	/* Dynamic Gear control(Counter type) */
#define	CPG_CDDIV5					(CPG_BASE + 0x414)	/* Dynamic Gear control(Counter type) */

#define	CPG_CSDIV0					(CPG_BASE + 0x500)	/* Static Gear control(Sparse type) */
#define	CPG_CSDIV1					(CPG_BASE + 0x504)	/* Static Gear control(Sparse type) */

#define	CPG_CLKON_0					(CPG_BASE + 0x600)	/* CGC control */
#define	CPG_CLKON_1					(CPG_BASE + 0x604)	/* CGC control */
#define	CPG_CLKON_2					(CPG_BASE + 0x608)	/* CGC control */
#define	CPG_CLKON_3					(CPG_BASE + 0x60c)	/* CGC control */
#define	CPG_CLKON_4					(CPG_BASE + 0x610)	/* CGC control */
#define	CPG_CLKON_5					(CPG_BASE + 0x614)	/* CGC control */
#define	CPG_CLKON_6					(CPG_BASE + 0x618)	/* CGC control */
#define	CPG_CLKON_7					(CPG_BASE + 0x61c)	/* CGC control */
#define	CPG_CLKON_8					(CPG_BASE + 0x620)	/* CGC control */
#define	CPG_CLKON_9					(CPG_BASE + 0x624)	/* CGC control */
#define	CPG_CLKON_10				(CPG_BASE + 0x628)	/* CGC control */
#define	CPG_CLKON_11				(CPG_BASE + 0x62c)	/* CGC control */
#define	CPG_CLKON_12				(CPG_BASE + 0x630)	/* CGC control */
#define	CPG_CLKON_13				(CPG_BASE + 0x634)	/* CGC control */
#define	CPG_CLKON_14				(CPG_BASE + 0x638)	/* CGC control */
#define	CPG_CLKON_15				(CPG_BASE + 0x63c)	/* CGC control */
#define	CPG_CLKON_16				(CPG_BASE + 0x640)	/* CGC control */
#define	CPG_CLKON_17				(CPG_BASE + 0x644)	/* CGC control */
#define	CPG_CLKON_18				(CPG_BASE + 0x648)	/* CGC control */
#define	CPG_CLKON_19				(CPG_BASE + 0x64c)	/* CGC control */
#define	CPG_CLKON_20				(CPG_BASE + 0x650)	/* CGC control */
#define	CPG_CLKON_21				(CPG_BASE + 0x654)	/* CGC control */
#define	CPG_CLKON_22				(CPG_BASE + 0x658)	/* CGC control */
#define	CPG_CLKON_23				(CPG_BASE + 0x65C)	/* CGC control */
#define	CPG_CLKON_24				(CPG_BASE + 0x660)	/* CGC control */

#define	CPG_CLKSTATUS0				(CPG_BASE + 0x700)	/* Dynamic gear/mux status monitor */

#define	CPG_CLKMON_0				(CPG_BASE + 0x800)	/* CGC monitor */
#define	CPG_CLKMON_1				(CPG_BASE + 0x804)	/* CGC monitor */
#define	CPG_CLKMON_2				(CPG_BASE + 0x808)	/* CGC monitor */
#define	CPG_CLKMON_3				(CPG_BASE + 0x80c)	/* CGC monitor */
#define	CPG_CLKMON_4				(CPG_BASE + 0x810)	/* CGC monitor */
#define	CPG_CLKMON_5				(CPG_BASE + 0x814)	/* CGC monitor */
#define	CPG_CLKMON_6				(CPG_BASE + 0x818)	/* CGC monitor */
#define	CPG_CLKMON_7				(CPG_BASE + 0x81c)	/* CGC monitor */
#define	CPG_CLKMON_8				(CPG_BASE + 0x820)	/* CGC monitor */
#define	CPG_CLKMON_9				(CPG_BASE + 0x824)	/* CGC monitor */
#define	CPG_CLKMON_10				(CPG_BASE + 0x828)	/* CGC monitor */

#define	CPG_RST_0					(CPG_BASE + 0x900)	/* RESET ON/OFF control */
#define	CPG_RST_1					(CPG_BASE + 0x904)	/* RESET ON/OFF control */
#define	CPG_RST_2					(CPG_BASE + 0x908)	/* RESET ON/OFF control */
#define	CPG_RST_3					(CPG_BASE + 0x90C)	/* RESET ON/OFF control */
#define	CPG_RST_4					(CPG_BASE + 0x910)	/* RESET ON/OFF control */
#define	CPG_RST_5					(CPG_BASE + 0x914)	/* RESET ON/OFF control */
#define	CPG_RST_6					(CPG_BASE + 0x918)	/* RESET ON/OFF control */
#define	CPG_RST_7					(CPG_BASE + 0x91C)	/* RESET ON/OFF control */
#define	CPG_RST_8					(CPG_BASE + 0x920)	/* RESET ON/OFF control */
#define	CPG_RST_9					(CPG_BASE + 0x924)	/* RESET ON/OFF control */
#define	CPG_RST_10					(CPG_BASE + 0x928)	/* RESET ON/OFF control */
#define	CPG_RST_11					(CPG_BASE + 0x92C)	/* RESET ON/OFF control */
#define	CPG_RST_12					(CPG_BASE + 0x930)	/* RESET ON/OFF control */
#define	CPG_RST_13					(CPG_BASE + 0x934)	/* RESET ON/OFF control */
#define	CPG_RST_14					(CPG_BASE + 0x938)	/* RESET ON/OFF control */
#define	CPG_RST_15					(CPG_BASE + 0x93C)	/* RESET ON/OFF control */
#define	CPG_RST_16					(CPG_BASE + 0x940)	/* RESET ON/OFF control */
#define	CPG_RST_17					(CPG_BASE + 0x944)	/* RESET ON/OFF control */

#define	CPG_RSTMON_0				(CPG_BASE + 0xA00)	/* RESET monitor */
#define	CPG_RSTMON_1				(CPG_BASE + 0xA04)	/* RESET monitor */
#define	CPG_RSTMON_2				(CPG_BASE + 0xA08)	/* RESET monitor */
#define	CPG_RSTMON_3				(CPG_BASE + 0xA0C)	/* RESET monitor */
#define	CPG_RSTMON_4				(CPG_BASE + 0xA10)	/* RESET monitor */
#define	CPG_RSTMON_5				(CPG_BASE + 0xA14)	/* RESET monitor */
#define	CPG_RSTMON_6				(CPG_BASE + 0xA18)	/* RESET monitor */
#define	CPG_RSTMON_7				(CPG_BASE + 0xA1C)	/* RESET monitor */
#define	CPG_RSTMON_8				(CPG_BASE + 0xA20)	/* RESET monitor */

#define	CPG_ERRORRST_SEL1			(CPG_BASE + 0xB00)	/* Error reset selection register */
#define	CPG_ERRORRST_SEL2			(CPG_BASE + 0xB04)	/* Error reset selection register */
#define	CPG_ERRORRST_SEL3			(CPG_BASE + 0xB08)	/* Error reset selection register */
#define	CPG_ERRORRST_SEL4			(CPG_BASE + 0xB0C)	/* Error reset selection register */
#define	CPG_ERRORRST_SEL5			(CPG_BASE + 0xB10)	/* Error reset selection register */
#define	CPG_ERRORRST_SEL6			(CPG_BASE + 0xB14)	/* Error reset selection register */
#define	CPG_ERRORRST_SEL7			(CPG_BASE + 0xB18)	/* Error reset selection register */
#define	CPG_ERRORRST_SEL8			(CPG_BASE + 0xB1C)	/* Error reset selection register */

#define	CPG_ERROR_RST2				(CPG_BASE + 0xB40)	/* Error reset register */
#define	CPG_ERROR_RST3				(CPG_BASE + 0xB44)	/* Error reset register */
#define	CPG_ERROR_RST4				(CPG_BASE + 0xB48)	/* Error reset register */
#define	CPG_ERROR_RST5				(CPG_BASE + 0xB4C)	/* Error reset register */
#define	CPG_ERROR_RST6				(CPG_BASE + 0xB50)	/* Error reset register */
#define	CPG_ERROR_RST7				(CPG_BASE + 0xB54)	/* Error reset register */
#define	CPG_ERROR_RST8				(CPG_BASE + 0xB58)	/* Error reset register */

#define	CPG_LP_CTL1					(CPG_BASE + 0xC00)	/* Lowpower Sequence Control Register 1 */
#define	CPG_LP_CTL2					(CPG_BASE + 0xC04)	/* Lowpower Sequence Control Register 2 */
#define	CPG_LP_GE3D_CTL				(CPG_BASE + 0xC08)	/* GPU Lowpower Sequence Control Register */
#define	CPG_CM33_CTL				(CPG_BASE + 0xC0C)	/* CM33 Control register */
#define	CPG_LP_CM33CTL0				(CPG_BASE + 0xC18)	/* Lowpower Sequence Cortex-M33 Control Register 0 */
#define	CPG_LP_CM33CTL1				(CPG_BASE + 0xC1C)	/* Lowpower Sequence Cortex-M33 Control Register 1 */
#define	CPG_LP_CA55_CTL1			(CPG_BASE + 0xC20)	/* Cortex-A55 Clock Control Register 1 */
#define	CPG_LP_CA55_CTL2			(CPG_BASE + 0xC24)	/* Cortex-A55 Clock Control Register 2 */
#define	CPG_LP_CA55_CTL3			(CPG_BASE + 0xC28)	/* Cortex-A55 Clock Control Register 3 */
#define	CPG_LP_CA55_CTL6			(CPG_BASE + 0xC34)	/* Cortex-A55 Clock Control Register 6 */
#define	CPG_LP_CA55_CTL7			(CPG_BASE + 0xC38)	/* Cortex-A55 Clock Control Register 7 */

#define	CPG_LP_PMU_CTL1				(CPG_BASE + 0xC4C)	/* Lowpower Sequence Control Register @ */
#define	CPG_LP_SRAM_STBY_CTL1		(CPG_BASE + 0xC50)	/* DRP SRAM standby control */
#define	CPG_LP_SRAM_STBY_CTL2		(CPG_BASE + 0xC54)	/* Shared SRAM standby control 0 */
#define	CPG_LP_SRAM_STBY_CTL3		(CPG_BASE + 0xC58)	/* Shared SRAM standby control 8 */
/*
 * TODO: Check CPG_LP_DDR_CTL1 value exists.
 * The manual does not include this register value, however it is necessary for the operation of the device.
 * An assumption has been made to it's existence.
 */
#define	CPG_LP_DDR_CTL1				(CPG_BASE + 0xC60)	/* DDR retention control */
#define	CPG_LP_CST_CTL2				(CPG_BASE + 0xC70)	/* CST control register 2 */
#define	CPG_LP_CST_CTL3				(CPG_BASE + 0xC74)	/* CST control register 3 */
#define	CPG_LP_PWC_CTL1				(CPG_BASE + 0xC78)	/* PWC control register 1 */
#define	CPG_LP_PWC_CTL2				(CPG_BASE + 0xC7C)	/* PWC control register 2 */

#define	CPG_DBGRST					(CPG_BASE + 0xC84)	/* Reset control register when CA55 is debugged */
#define	OTP_HANDSHAKE_MON			(CPG_BASE + 0xC88)	/* OTP handshake monitor register */
#define	CPG_OTHERS_INI				(CPG_BASE + 0xC8C)	/* Others area reset control */
#define CPG_LP_NPU_CTL1				(CPG_BASE + 0xC94)	
#define CPG_LP_NPU_CTL2				(CPG_BASE + 0xC98)
#define CPG_LP_VSPI_CTL1			(CPG_BASE + 0xC9C)
#define CPG_LP_VSPI_CTL2			(CPG_BASE + 0xCA0)
#define CPG_LP_FDP1_CTL1			(CPG_BASE + 0xCA4)

#define	CPG_BUS_1_MSTOP				(CPG_BASE + 0xD00)	/* MSTOP register 1 */
#define	CPG_BUS_2_MSTOP				(CPG_BASE + 0xD04)	/* MSTOP register 2 */
#define	CPG_BUS_3_MSTOP				(CPG_BASE + 0xD08)	/* MSTOP register 3 */
#define	CPG_BUS_4_MSTOP				(CPG_BASE + 0xD0C)	/* MSTOP register 4 */
#define	CPG_BUS_5_MSTOP				(CPG_BASE + 0xD10)	/* MSTOP register 5 */
#define	CPG_BUS_6_MSTOP				(CPG_BASE + 0xD14)	/* MSTOP register 6 */
#define	CPG_BUS_7_MSTOP				(CPG_BASE + 0xD18)	/* MSTOP register 7 */
#define	CPG_BUS_8_MSTOP				(CPG_BASE + 0xD1C)	/* MSTOP register 8 */
#define	CPG_BUS_9_MSTOP				(CPG_BASE + 0xD20)	/* MSTOP register 9 */
#define	CPG_BUS_10_MSTOP			(CPG_BASE + 0xD24)	/* MSTOP register 10*/
#define	CPG_BUS_11_MSTOP			(CPG_BASE + 0xD28)	/* MSTOP register 11 */
#define	CPG_BUS_12_MSTOP			(CPG_BASE + 0xD2C)	/* MSTOP register 12 */



#define CPG_PLL_STBY_RESETB					(1UL << 0)
#define CPG_PLL_STBY_SSC_EN					(1UL << 2)
#define CPG_PLL_STBY_RESETB_WEN				(1UL << 16)
#define CPG_PLL_STBY_SSC_EN_WEN				(1UL << 18)

#define CPG_PLL_CLK1_DIV_P					(1UL << 0)
#define CPG_PLL_CLK1_DIV_M					(1UL << 6)
#define CPG_PLL_CLK1_DIV_K					(1UL << 16)

#define CPG_PLL_CLK2_DIV_S					(1UL << 0)

#define CPG_PLL_MON_PLLn_RESETB				(1UL << 0)
#define CPG_PLL_MON_PLLn_LOCK				(1UL << 4)

#define CPG_BUS_1_MSTOP_WDT1				(1UL << 0)
#define CPG_BUS_1_MSTOP_RIIC0				(1UL << 1)
#define CPG_BUS_1_MSTOP_RIIC1				(1UL << 2)
#define CPG_BUS_1_MSTOP_RIIC2				(1UL << 3)
#define CPG_BUS_1_MSTOP_RIIC3				(1UL << 4)
#define CPG_BUS_1_MSTOP_RIIC4				(1UL << 5)
#define CPG_BUS_1_MSTOP_RIIC5				(1UL << 6)
#define CPG_BUS_1_MSTOP_RIIC6				(1UL << 7)
#define CPG_BUS_1_MSTOP_RIIC7				(1UL << 8)
#define CPG_BUS_1_MSTOP_SPDIF0				(1UL << 9)
#define CPG_BUS_1_MSTOP_SPDIF1				(1UL << 10)
#define CPG_BUS_1_MSTOP_SPDIF2				(1UL << 11)
/* Bits 12 and 13 are reserved */
#define CPG_BUS_1_MSTOP_ACPU_TO_RCPU		(1UL << 14)
#define CPG_BUS_1_MSTOP_PCIE				(1UL << 15)

#define CPG_BUS_2_MSTOP_SCU					(1UL << 0)
#define CPG_BUS_2_MSTOP_SCU_DMAC			(1UL << 1)
#define CPG_BUS_2_MSTOP_ADG					(1UL << 2)
#define CPG_BUS_2_MSTOP_SSIU				(1UL << 3)
#define CPG_BUS_2_MSTOP_SSIU_DMAC			(1UL << 4)
#define CPG_BUS_2_MSTOP_ADMAC				(1UL << 5)
#define CPG_BUS_2_MSTOP_TZC400_DDR00		(1UL << 6)
#define CPG_BUS_2_MSTOP_TZC400_DDR01		(1UL << 7)
/* Bits 8 and 9 are reserved */
#define CPG_BUS_2_MSTOP_TZC400_AXI_RCPU		(1UL << 10)
#define CPG_BUS_2_MSTOP_TZC400_SRAMA		(1UL << 11)
#define CPG_BUS_2_MSTOP_TZC400_PCIE			(1UL << 12)
#define CPG_BUS_2_MSTOP_GTM2				(1UL << 13)
#define CPG_BUS_2_MSTOP_GTM3				(1UL << 14)
#define CPG_BUS_2_MSTOP_TSU1				(1UL << 15)

#define CPG_BUS_3_MSTOP_SYC					(1UL << 0)
/* Bit 1 is reserved */
#define CPG_BUS_3_MSTOP_DMAC1				(1UL << 2)
#define CPG_BUS_3_MSTOP_DMAC2				(1UL << 3)
#define CPG_BUS_3_MSTOP_GE3D				(1UL << 4)
#define CPG_BUS_3_MSTOP_GIC					(1UL << 5)
#define CPG_BUS_3_MSTOP_GPV_ACPU			(1UL << 6)
#define CPG_BUS_3_MSTOP_GPV_ACPU_REG0		(1UL << 7)
#define CPG_BUS_3_MSTOP_GPV_ACPU_REG1		(1UL << 8)
#define CPG_BUS_3_MSTOP_ADC					(1UL << 9)
#define CPG_BUS_3_MSTOP_WDT0				(1UL << 10)
#define CPG_BUS_3_MSTOP_RTC_P0				(1UL << 11)
#define CPG_BUS_3_MSTOP_RTC_P1				(1UL << 12)
#define CPG_BUS_3_MSTOP_RIIC8				(1UL << 13)
#define CPG_BUS_3_MSTOP_SCIF				(1UL << 14)
#define CPG_BUS_3_MSTOP_CMTW0				(1UL << 15)

#define CPG_BUS_4_MSTOP_CMTW1				(1UL << 0)
#define CPG_BUS_4_MSTOP_CMTW2				(1UL << 1)
#define CPG_BUS_4_MSTOP_CMTW3				(1UL << 2)
#define CPG_BUS_4_MSTOP_SRAM0				(1UL << 3)
/* Bit 4 is reserved */
#define CPG_BUS_4_MSTOP_XSPI				(1UL << 5)
/* Bit 6 is reserved */
#define CPG_BUS_4_MSTOP_PFC					(1UL << 7)
/* Bits 8 to 10 are reserved */
#define CPG_BUS_4_MSTOP_OTP					(1UL << 11)
#define CPG_BUS_4_MSTOP_TZC400_SRAMM		(1UL << 12)
#define CPG_BUS_4_MSTOP_TZC400_XSPI			(1UL << 13)
#define CPG_BUS_4_MSTOP_MHU					(1UL << 14)
/* Bit 15 is reserved */

/* Bit 0 is reserved */
#define CPG_BUS_5_MSTOP_CST					(1UL << 1)
/* Bit 2 is reserved */
#define CPG_BUS_5_MSTOP_SRAM0_REG			(1UL << 3)
/* Bit 4 is reserved */
#define CPG_BUS_5_MSTOP_XSPI_REG			(1UL << 5)
#define CPG_BUS_5_MSTOP_PDM0				(1UL << 6)
#define CPG_BUS_5_MSTOP_PDM1				(1UL << 7)
#define CPG_BUS_5_MSTOP_GPV_MCPU			(1UL << 8)
#define CPG_BUS_5_MSTOP_DMAC0				(1UL << 9)
#define CPG_BUS_5_MSTOP_GTM0				(1UL << 10)
#define CPG_BUS_5_MSTOP_GTM1				(1UL << 11)
#define CPG_BUS_5_MSTOP_WDT2				(1UL << 12)
#define CPG_BUS_5_MSTOP_WDT3				(1UL << 13)
#define CPG_BUS_5_MSTOP_CRC					(1UL << 14)
#define CPG_BUS_5_MSTOP_CMTW4				(1UL << 15)

#define CPG_BUS_6_MSTOP_CMTW5				(1UL << 0)
#define CPG_BUS_6_MSTOP_CMTW6				(1UL << 1)
#define CPG_BUS_6_MSTOP_CMTW7				(1UL << 2)
#define CPG_BUS_6_MSTOP_POEG0A				(1UL << 3)
#define CPG_BUS_6_MSTOP_POEG0B				(1UL << 4)
#define CPG_BUS_6_MSTOP_POEG0C				(1UL << 5)
#define CPG_BUS_6_MSTOP_POEG0D				(1UL << 6)
#define CPG_BUS_6_MSTOP_POEG1A				(1UL << 7)
#define CPG_BUS_6_MSTOP_POEG1B				(1UL << 8)
#define CPG_BUS_6_MSTOP_POEG1C				(1UL << 9)
#define CPG_BUS_6_MSTOP_POEG1D				(1UL << 10)
#define CPG_BUS_6_MSTOP_GPT0				(1UL << 11)
#define CPG_BUS_6_MSTOP_GPT1				(1UL << 12)
#define CPG_BUS_6_MSTOP_DDR0_P0				(1UL << 13)
#define CPG_BUS_6_MSTOP_DDR0_P1				(1UL << 14)
#define CPG_BUS_6_MSTOP_DDR0_P2				(1UL << 15)

#define CPG_BUS_7_MSTOP_DDR_0_P3			(1UL << 0)
#define CPG_BUS_7_MSTOP_DDR_0_P4			(1UL << 1)
/* Bits 2 to 6 are reserved */
#define CPG_BUS_7_MSTOP_USB20_HOST			(1UL << 7)
#define CPG_BUS_7_MSTOP_USB21_HOST			(1UL << 8)
#define CPG_BUS_7_MSTOP_USB2_FUNC			(1UL << 9)
#define CPG_BUS_7_MSTOP_USB20_PHY			(1UL << 10)
#define CPG_BUS_7_MSTOP_USB21_PHY			(1UL << 11)
#define CPG_BUS_7_MSTOP_USB30_HOST			(1UL << 12)
/* Bit 13 is reserved */
#define CPG_BUS_7_MSTOP_USB30_PHY			(1UL << 14)
/* Bit 15 is reserved */

 #define CPG_BUS_8_MSTOP_PCIE_PHY			(1UL << 0)
 #define CPG_BUS_8_MSTOP_GPV_COM_SUB			(1UL << 1)
#define CPG_BUS_8_MSTOP_SD0					(1UL << 2)
#define CPG_BUS_8_MSTOP_SD1					(1UL << 3)
#define CPG_BUS_8_MSTOP_SD2					(1UL << 4)
#define CPG_BUS_8_MSTOP_GBETH0				(1UL << 5)
#define CPG_BUS_8_MSTOP_GBETH1				(1UL << 6)
#define CPG_BUS_8_MSTOP_GPV_COM				(1UL << 7)
/* Bits 8 to 10 are reserved */
#define CPG_BUS_8_MSTOP_NPU_GPV				(1UL << 11)
#define CPG_BUS_8_MSTOP_SRAM1_REG			(1UL << 12)
/* Bits 13 to 15 are reserved */

/* Bits 0 to 3 are reserved */
#define CPG_BUS_9_MSTOP_CRU0				(1UL << 4)
/* Bits 5 to 9 are reserved */
#define CPG_BUS_9_MSTOP_GPV_VIDEO0			(1UL << 10)
#define CPG_BUS_9_MSTOP_VCD_P0				(1UL << 11)
#define CPG_BUS_9_MSTOP_VCD_P1				(1UL << 12)
#define CPG_BUS_9_MSTOP_VCD_P2				(1UL << 13)
#define CPG_BUS_9_MSTOP_DSI_LINK			(1UL << 14)
#define CPG_BUS_9_MSTOP_DSI_PHY				(1UL << 15)

/* Bit 0 is reserved */
#define CPG_BUS_10_MSTOP_LCDC_0_DU			(1UL << 1)
#define CPG_BUS_10_MSTOP_LCDC_0_FCPVD		(1UL << 2)
#define CPG_BUS_10_MSTOP_LCDC_0_VSPD		(1UL << 3)
#define CPG_BUS_10_MSTOP_GPV_VIDEO1			(1UL << 4)
#define CPG_BUS_10_MSTOP_DDR0_PHY			(1UL << 5)
/* Bit 6 is reserved */
#define CPG_BUS_10_MSTOP_DDR0_CTRL			(1UL << 7)
/* Bits 8 to 10 are reserved */
#define CPG_BUS_10_MSTOP_DMAC3				(1UL << 11)
#define CPG_BUS_10_MSTOP_DMAC4				(1UL << 12)
/* Bit 13 is reserved */
#define CPG_BUS_10_MSTOP_CANFD				(1UL << 14)
#define CPG_BUS_10_MSTOP_I3C0				(1UL << 15)

#define CPG_BUS_11_MSTOP_RSPI0				(1UL << 0)
#define CPG_BUS_11_MSTOP_RSPI1				(1UL << 1)
#define CPG_BUS_11_MSTOP_RSPI2				(1UL << 2)
#define CPG_BUS_11_MSTOP_RSCI0				(1UL << 3)
#define CPG_BUS_11_MSTOP_RSCI1				(1UL << 4)
#define CPG_BUS_11_MSTOP_RSCI2				(1UL << 5)
#define CPG_BUS_11_MSTOP_RSCI3				(1UL << 6)
#define CPG_BUS_11_MSTOP_RSCI4				(1UL << 7)
#define CPG_BUS_11_MSTOP_RSCI5				(1UL << 8)
#define CPG_BUS_11_MSTOP_RSCI6				(1UL << 9)
#define CPG_BUS_11_MSTOP_RSCI7				(1UL << 10)
#define CPG_BUS_11_MSTOP_RSCI8				(1UL << 11)
#define CPG_BUS_11_MSTOP_RSCI9				(1UL << 12)
#define CPG_BUS_11_MSTOP_GTM4				(1UL << 13)
#define CPG_BUS_11_MSTOP_GTM5				(1UL << 14)
#define CPG_BUS_11_MSTOP_GTM6				(1UL << 15)

#define CPG_BUS_12_MSTOP_GTM7				(1UL << 0)
#define CPG_BUS_12_MSTOP_SRAM4				(1UL << 1)
/* Bits 2 to 8 are reserved */
#define CPG_BUS_12_MSTOP_MCPU_TO_ACPU		(1UL << 9)
#define CPG_BUS_12_MSTOP_ACPU_TO_MCPU		(1UL << 10)
/* Bits 11 to 15 are reserved */

#define CPG_BUS_13_MSTOP_LVDS				(1UL << 0)
#define CPG_BUS_13_MSTOP_VSPI				(1UL << 1)
#define CPG_BUS_13_MSTOP_VSPI1				(1UL << 2)
#define CPG_BUS_13_MSTOP_LCDC_1_DU			(1UL << 3)
#define CPG_BUS_13_MSTOP_LCDC_1_FCPVD		(1UL << 4)
#define CPG_BUS_13_MSTOP_LCDC_1_VSPD		(1UL << 5)
#define CPG_BUS_13_MSTOP_NPU				(1UL << 6)
#define CPG_BUS_13_MSTOP_SHIPG				(1UL << 7)
#define CPG_BUS_13_MSTOP_SHIP				(1UL << 8)
#define CPG_BUS_13_MSTOP_FDP1				(1UL << 9)
#define CPG_BUS_13_MSTOP_FDP1_FCPF			(1UL << 10)
/* Bits 11 to 15 are reserved */

#define CPG_ERRORRST_SELx_ERRRSTSEL0		(1UL << 0)
#define CPG_ERRORRST_SELx_ERRRSTSEL1		(1UL << 1)
#define CPG_ERRORRST_SELx_ERRRSTSEL2		(1UL << 2)
#define CPG_ERRORRST_SELx_ERRRSTSEL3		(1UL << 3)

#define CPG_LP_CTL1_STBY					(0x00000001UL)
#define CPG_LP_CTL1_STBY_MSK				(0x00000001UL)
#define CPG_LP_CTL1_CA55SLEEP_REQ			(0x00000100UL)
#define CPG_LP_CTL1_CA55SLEEP_REQ_MSK		(0x00000F00UL)
#define CPG_LP_CTL1_CA55SLEEP_ACK			(0x01000000UL)
#define CPG_LP_CTL1_CA55SLEEP_ACK_MSK		(0x0F000000UL)

#define CPG_LP_CA55_CTL2_COREPREQ0			(1UL << 0)
#define CPG_LP_CA55_CTL2_COREPREQ1			(1UL << 16)
#define CPG_LP_CA55_CTL3_COREPREQ2			(1UL << 0)
#define CPG_LP_CA55_CTL3_COREPREQ3			(1UL << 16)

#define CPG_LP_CA55_CTL2_CORESTATE0			(1UL << 1)
#define CPG_LP_CA55_CTL2_CORESTATE1			(1UL << 17)
#define CPG_LP_CA55_CTL3_CORESTATE2			(1UL << 1)
#define CPG_LP_CA55_CTL3_CORESTATE3			(1UL << 17)

#define CPG_LP_CA55_CTL2_CORESTATE0_ON_MASK	(1UL << 4)
#define CPG_LP_CA55_CTL2_CORESTATE1_ON_MASK	(1UL << 20)
#define CPG_LP_CA55_CTL3_CORESTATE2_ON_MASK	(1UL << 4)
#define CPG_LP_CA55_CTL3_CORESTATE3_ON_MASK	(1UL << 20)

#define CPG_LP_CA55_CTL2_COREACCEPT0		(1UL << 8)
#define CPG_LP_CA55_CTL2_COREACCEPT1		(1UL << 24)
#define CPG_LP_CA55_CTL3_COREACCEPT2		(1UL << 8)
#define CPG_LP_CA55_CTL3_COREACCEPT3		(1UL << 24)


#define CPG_REG_PLLCM33_STBY				(CPG_BASE + 0x0000)
#define CPG_REG_PLLCM33_CLK1				(CPG_BASE + 0x0004)
#define CPG_REG_PLLCM33_CLK2				(CPG_BASE + 0x0008)
#define CPG_REG_PLLCM33_CLK3				(CPG_BASE + 0x000C)
#define CPG_REG_PLLCM33_MON 				(CPG_BASE + 0x0010)

#define CPG_REG_PLLCLN_STBY 				(CPG_BASE + 0x0020)
#define CPG_REG_PLLCLN_CLK1 				(CPG_BASE + 0x0024)
#define CPG_REG_PLLCLN_CLK2 				(CPG_BASE + 0x0028)
#define CPG_REG_PLLCLN_CLK3 				(CPG_BASE + 0x002C)
#define CPG_REG_PLLCLN_MON					(CPG_BASE + 0x0030)

#define CPG_REG_PLLDTY_STBY 				(CPG_BASE + 0x0040)
#define CPG_REG_PLLDTY_CLK1 				(CPG_BASE + 0x0044)
#define CPG_REG_PLLDTY_CLK2 				(CPG_BASE + 0x0048)
#define CPG_REG_PLLDTY_CLK3 				(CPG_BASE + 0x004C)
#define CPG_REG_PLLDTY_MON					(CPG_BASE + 0x0050)

#define CPG_REG_PLLCA55_STBY				(CPG_BASE + 0x0060)
#define CPG_REG_PLLCA55_CLK1				(CPG_BASE + 0x0064)
#define CPG_REG_PLLCA55_CLK2				(CPG_BASE + 0x0068)
#define CPG_REG_PLLCA55_CLK3				(CPG_BASE + 0x006C)
#define CPG_REG_PLLCA55_MON 				(CPG_BASE + 0x0070)

#define CPG_REG_PLLVDO_STBY 				(CPG_BASE + 0x0080)
#define CPG_REG_PLLVDO_CLK1 				(CPG_BASE + 0x0084)
#define CPG_REG_PLLVDO_CLK2 				(CPG_BASE + 0x0088)
#define CPG_REG_PLLVDO_CLK3 				(CPG_BASE + 0x008C)
#define CPG_REG_PLLVDO_MON					(CPG_BASE + 0x0090)

#define CPG_REG_PLLETH_STBY 				(CPG_BASE + 0x00A0)
#define CPG_REG_PLLETH_CLK1 				(CPG_BASE + 0x00A4)
#define CPG_REG_PLLETH_CLK2 				(CPG_BASE + 0x00A8)
#define CPG_REG_PLLETH_CLK3 				(CPG_BASE + 0x00AC)
#define CPG_REG_PLLETH_MON					(CPG_BASE + 0x00B0)

#define CPG_REG_PLLDSI_STBY 				(CPG_BASE + 0x00C0)
#define CPG_REG_PLLDSI_CLK1 				(CPG_BASE + 0x00C4)
#define CPG_REG_PLLDSI_CLK2 				(CPG_BASE + 0x00C8)
#define CPG_REG_PLLDSI_CLK3 				(CPG_BASE + 0x00CC)
#define CPG_REG_PLLDSI_MON					(CPG_BASE + 0x00D0)

#define CPG_REG_PLLDDR0_STBY				(CPG_BASE + 0x00E0)
#define CPG_REG_PLLDDR0_CLK1				(CPG_BASE + 0x00E4)
#define CPG_REG_PLLDDR0_CLK2				(CPG_BASE + 0x00E8)
#define CPG_REG_PLLDDR0_CLK3				(CPG_BASE + 0x00EC)
#define CPG_REG_PLLDDR0_MON 				(CPG_BASE + 0x00F0)

#define CPG_REG_PLLDSI1_STBY				(CPG_BASE + 0x0160)
#define CPG_REG_PLLDSI1_CLK1				(CPG_BASE + 0x0164)
#define CPG_REG_PLLDSI1_CLK2				(CPG_BASE + 0x0168)
#define CPG_REG_PLLDSI1_CLK3				(CPG_BASE + 0x016C)
#define CPG_REG_PLLDSI1_MON 				(CPG_BASE + 0x0170)

#define CPG_REG_CLMA2_CTL					(CPG_BASE + 0x0208)
#define CPG_REG_CLMA3_CTL					(CPG_BASE + 0x020C)
#define CPG_REG_CLMA4_CTL					(CPG_BASE + 0x0210)
#define CPG_REG_CLMA5_CTL					(CPG_BASE + 0x0214)
#define CPG_REG_CLMA6_CTL					(CPG_BASE + 0x0218)
#define CPG_REG_CLMA7_CTL					(CPG_BASE + 0x021C)
#define CPG_REG_CLMA8_CTL					(CPG_BASE + 0x0220)
#define CPG_REG_CLMA9_CTL					(CPG_BASE + 0x0224)
#define CPG_REG_CLMA10_CTL					(CPG_BASE + 0x0228)
#define CPG_REG_CLMA11_CTL					(CPG_BASE + 0x022C)
#define CPG_REG_CLMA15_CTL					(CPG_BASE + 0x023C)
#define CPG_REG_CLMA_MON					(CPG_BASE + 0x0280)

#define CPG_REG_SSEL0						(CPG_BASE + 0x0300)
#define CPG_REG_SSEL1						(CPG_BASE + 0x0304)
#define CPG_REG_SSEL3						(CPG_BASE + 0x030C)

#define CPG_REG_CDDIV0						(CPG_BASE + 0x0400)
#define CPG_REG_CDDIV1						(CPG_BASE + 0x0404)
#define CPG_REG_CDDIV2						(CPG_BASE + 0x0408)
#define CPG_REG_CDDIV3						(CPG_BASE + 0x040C)
#define CPG_REG_CDDIV4						(CPG_BASE + 0x0410)
#define CPG_REG_CDDIV5						(CPG_BASE + 0x0414)

#define CPG_REG_CSDIV0						(CPG_BASE + 0x0500)
#define CPG_REG_CSDIV1						(CPG_BASE + 0x0504)

#define CPG_REG_CLKON0						(CPG_BASE + 0x0600)
#define CPG_REG_CLKON1						(CPG_BASE + 0x0604)
#define CPG_REG_CLKON2						(CPG_BASE + 0x0608)
#define CPG_REG_CLKON3						(CPG_BASE + 0x060C)
#define CPG_REG_CLKON4						(CPG_BASE + 0x0610)
#define CPG_REG_CLKON5						(CPG_BASE + 0x0614)
#define CPG_REG_CLKON6						(CPG_BASE + 0x0618)
#define CPG_REG_CLKON7						(CPG_BASE + 0x061C)
#define CPG_REG_CLKON8						(CPG_BASE + 0x0620)
#define CPG_REG_CLKON9						(CPG_BASE + 0x0624)
#define CPG_REG_CLKON10 					(CPG_BASE + 0x0628)
#define CPG_REG_CLKON11 					(CPG_BASE + 0x062C)
#define CPG_REG_CLKON12 					(CPG_BASE + 0x0630)
#define CPG_REG_CLKON13 					(CPG_BASE + 0x0634)
#define CPG_REG_CLKON14 					(CPG_BASE + 0x0638)
#define CPG_REG_CLKON15 					(CPG_BASE + 0x063C)
#define CPG_REG_CLKON16 					(CPG_BASE + 0x0640)
#define CPG_REG_CLKON17 					(CPG_BASE + 0x0644)
#define CPG_REG_CLKON18 					(CPG_BASE + 0x0648)
#define CPG_REG_CLKON19 					(CPG_BASE + 0x064C)
#define CPG_REG_CLKON20 					(CPG_BASE + 0x0650)
#define CPG_REG_CLKON21 					(CPG_BASE + 0x0654)
#define CPG_REG_CLKON22 					(CPG_BASE + 0x0658)
#define CPG_REG_CLKON23 					(CPG_BASE + 0x065C)
#define CPG_REG_CLKON24 					(CPG_BASE + 0x0660)
#define CPG_REG_CLKON25 					(CPG_BASE + 0x0664)
#define CPG_REG_CLKON26 					(CPG_BASE + 0x0668)
#define CPG_REG_CLKON27 					(CPG_BASE + 0x066C)

#define CPG_REG_CLKSTATUS0					(CPG_BASE + 0x0700)

#define CPG_REG_CLKMON0 					(CPG_BASE + 0x0800)
#define CPG_REG_CLKMON1 					(CPG_BASE + 0x0804)
#define CPG_REG_CLKMON2 					(CPG_BASE + 0x0808)
#define CPG_REG_CLKMON3 					(CPG_BASE + 0x080C)
#define CPG_REG_CLKMON4 					(CPG_BASE + 0x0810)
#define CPG_REG_CLKMON5 					(CPG_BASE + 0x0814)
#define CPG_REG_CLKMON6 					(CPG_BASE + 0x0818)
#define CPG_REG_CLKMON7 					(CPG_BASE + 0x081C)
#define CPG_REG_CLKMON8 					(CPG_BASE + 0x0820)
#define CPG_REG_CLKMON9 					(CPG_BASE + 0x0824)
#define CPG_REG_CLKMON10					(CPG_BASE + 0x0828)
#define CPG_REG_CLKMON11					(CPG_BASE + 0x082C)

#define CPG_REG_RST0						(CPG_BASE + 0x0900)
#define CPG_REG_RST1						(CPG_BASE + 0x0904)
#define CPG_REG_RST3						(CPG_BASE + 0x090C)
#define CPG_REG_RST4						(CPG_BASE + 0x0910)
#define CPG_REG_RST5						(CPG_BASE + 0x0914)
#define CPG_REG_RST6						(CPG_BASE + 0x0918)
#define CPG_REG_RST7						(CPG_BASE + 0x091C)
#define CPG_REG_RST8						(CPG_BASE + 0x0920)
#define CPG_REG_RST9						(CPG_BASE + 0x0924)
#define CPG_REG_RST10						(CPG_BASE + 0x0928)
#define CPG_REG_RST11						(CPG_BASE + 0x092C)
#define CPG_REG_RST12						(CPG_BASE + 0x0930)
#define CPG_REG_RST13						(CPG_BASE + 0x0934)
#define CPG_REG_RST14						(CPG_BASE + 0x0938)
#define CPG_REG_RST15						(CPG_BASE + 0x093C)
#define CPG_REG_RST16						(CPG_BASE + 0x0940)
#define CPG_REG_RST17						(CPG_BASE + 0x0944)
#define CPG_REG_RST18						(CPG_BASE + 0x0948)

#define CPG_REG_RSTMON0 					(CPG_BASE + 0x0A00)
#define CPG_REG_RSTMON1 					(CPG_BASE + 0x0A04)
#define CPG_REG_RSTMON2 					(CPG_BASE + 0x0A08)
#define CPG_REG_RSTMON3 					(CPG_BASE + 0x0A0C)
#define CPG_REG_RSTMON4 					(CPG_BASE + 0x0A10)
#define CPG_REG_RSTMON5 					(CPG_BASE + 0x0A14)
#define CPG_REG_RSTMON6 					(CPG_BASE + 0x0A18)
#define CPG_REG_RSTMON7 					(CPG_BASE + 0x0A1C)
#define CPG_REG_RSTMON8 					(CPG_BASE + 0x0A20)
#define CPG_REG_RSTMON9 					(CPG_BASE + 0x0A24)

#define CPG_REG_ERRORRST_SEL1				(CPG_BASE + 0x0B00)
#define CPG_REG_ERRORRST_SEL2				(CPG_BASE + 0x0B04)
#define CPG_REG_ERRORRST_SEL3				(CPG_BASE + 0x0B08)
#define CPG_REG_ERRORRST_SEL4				(CPG_BASE + 0x0B0C)
#define CPG_REG_ERRORRST_SEL5				(CPG_BASE + 0x0B10)
#define CPG_REG_ERRORRST_SEL6				(CPG_BASE + 0x0B14)
#define CPG_REG_ERRORRST_SEL7				(CPG_BASE + 0x0B18)
#define CPG_REG_ERRORRST_SEL8				(CPG_BASE + 0x0B1C)

#define CPG_REG_ERROR_RST2					(CPG_BASE + 0x0B40)
#define CPG_REG_ERROR_RST3					(CPG_BASE + 0x0B44)
#define CPG_REG_ERROR_RST4					(CPG_BASE + 0x0B48)
#define CPG_REG_ERROR_RST5					(CPG_BASE + 0x0B4C)
#define CPG_REG_ERROR_RST6					(CPG_BASE + 0x0B50)
#define CPG_REG_ERROR_RST7					(CPG_BASE + 0x0B54)
#define CPG_REG_ERROR_RST8					(CPG_BASE + 0x0B58)

#define CPG_REG_LP_CTL1 					(CPG_BASE + 0x0C00)
#define CPG_REG_LP_CTL2 					(CPG_BASE + 0x0C04)
#define CPG_REG_LP_GE3D_CTL 				(CPG_BASE + 0x0C08)

#define CPG_REG_CM33_CTL					(CPG_BASE + 0x0C0C)

#define CPG_REG_LP_CM33_CTL0				(CPG_BASE + 0x0C18)
#define CPG_REG_LP_CM33_CTL1				(CPG_BASE + 0x0C1C)
#define CPG_REG_LP_CA55_CTL1				(CPG_BASE + 0x0C20)
#define CPG_REG_LP_CA55_CTL2				(CPG_BASE + 0x0C24)
#define CPG_REG_LP_CA55_CTL3				(CPG_BASE + 0x0C28)
#define CPG_REG_LP_CA55_CTL4				(CPG_BASE + 0x0C2C)
#define CPG_REG_LP_CA55_CTL5				(CPG_BASE + 0x0C30)
#define CPG_REG_LP_CA55_CTL6				(CPG_BASE + 0x0C34)
#define CPG_REG_LP_CA55_CTL7				(CPG_BASE + 0x0C38)
#define CPG_REG_LP_PMU_CTL1 				(CPG_BASE + 0x0C4C)
#define CPG_REG_LP_SRAM_STBY_CTL1			(CPG_BASE + 0x0C50)
#define CPG_REG_LP_SRAM_STBY_CTL2			(CPG_BASE + 0x0C54)
#define CPG_REG_LP_SRAM_STBY_CTL3			(CPG_BASE + 0x0C58)
#define CPG_REG_LP_GIC_CTL1 				(CPG_BASE + 0x0C5C)
#define CPG_REG_LP_DDR_CTL1 				(CPG_BASE + 0x0C60)
#define CPG_REG_LP_OTP_CTL1 				(CPG_BASE + 0x0C64)
#define CPG_REG_LP_CM33CTL_INI				(CPG_BASE + 0x0C68)
#define CPG_REG_LP_CST_CTL1 				(CPG_BASE + 0x0C6C)
#define CPG_REG_LP_CST_CTL2 				(CPG_BASE + 0x0C70)
#define CPG_REG_LP_CST_CTL3 				(CPG_BASE + 0x0C74)
#define CPG_REG_LP_PWC_CTL1 				(CPG_BASE + 0x0C78)
#define CPG_REG_LP_PWC_CTL2 				(CPG_BASE + 0x0C7C)
#define CPG_REG_LP_OSTMTCKE 				(CPG_BASE + 0x0C80)
#define CPG_REG_DBGRST						(CPG_BASE + 0x0C84)
#define CPG_REG_HANDSHAKE_MON				(CPG_BASE + 0x0C88)
#define CPG_REG_OTHERS_INI					(CPG_BASE + 0x0C8C)
#define CPG_REG_CM33_STATE_MON				(CPG_BASE + 0x0C90)
#define CPG_REG_LP_NPU_CTL1 				(CPG_BASE + 0x0C94)
#define CPG_REG_LP_NPU_CTL2 				(CPG_BASE + 0x0C98)
#define CPG_REG_LP_VSPI_CTL1				(CPG_BASE + 0x0C9C)
#define CPG_REG_LP_VSPI_CTL2				(CPG_BASE + 0x0CA0)
#define CPG_REG_LP_FDP1_CTL1				(CPG_BASE + 0x0CA4)

#define CPG_REG_BUS_1_MSTOP 				(CPG_BASE + 0x0D00)
#define CPG_REG_BUS_2_MSTOP 				(CPG_BASE + 0x0D04)
#define CPG_REG_BUS_3_MSTOP 				(CPG_BASE + 0x0D08)
#define CPG_REG_BUS_4_MSTOP 				(CPG_BASE + 0x0D0C)
#define CPG_REG_BUS_5_MSTOP 				(CPG_BASE + 0x0D10)
#define CPG_REG_BUS_6_MSTOP 				(CPG_BASE + 0x0D14)
#define CPG_REG_BUS_7_MSTOP 				(CPG_BASE + 0x0D18)
#define CPG_REG_BUS_8_MSTOP 				(CPG_BASE + 0x0D1C)
#define CPG_REG_BUS_9_MSTOP 				(CPG_BASE + 0x0D20)
#define CPG_REG_BUS_10_MSTOP				(CPG_BASE + 0x0D24)
#define CPG_REG_BUS_11_MSTOP				(CPG_BASE + 0x0D28)
#define CPG_REG_BUS_12_MSTOP				(CPG_BASE + 0x0D2C)
#define CPG_REG_BUS_13_MSTOP				(CPG_BASE + 0x0D30)

#define CPG_REG_RSV1						(CPG_BASE + 0x0E00)
#define CPG_REG_RSV2						(CPG_BASE + 0x0E04)
#define CPG_REG_RSV3						(CPG_BASE + 0x0E08)
#define CPG_REG_RSV4						(CPG_BASE + 0x0E0C)
#define CPG_REG_RSV5						(CPG_BASE + 0x0E10)
#define CPG_REG_RSV6						(CPG_BASE + 0x0E14)

#if 1
typedef struct cpg_clkrst_data
{
	uintptr_t p_reg; /* CPG set register address */
	uintptr_t p_mon; /* Monitor register address */
	uint32_t setval; /* set value */
	uint32_t monval; /* monitor mask value */
	uint32_t onoff; /* select ON/OFF */
	uint32_t clkrst; /* select CLKON/RSTOFF */
} st_cpg_clkrst_data_t;

#define CPG_MSTOP_RUN		(0x55555555ul)
#define CPG_MSTOP_STOP		(0xAAAAAAAAul)
#define CPG_CLKRST_ON		(0x55555555ul)
#define CPG_CLKRST_OFF		(0xAAAAAAAAul)

#define CPG_CTRL_CLK		(0xAAAAAAAAul)
#define CPG_CTRL_RST		(0x55555555ul)

/*** Bit define of MSTOP register ***/
#define CPG_BUS_1_MSTOP_INIT		(0xCFFF0FFFuL)				/* Init value of MSTOP1 */
#define CPG_BUS_2_MSTOP_INIT		(0xE4FFE03FuL)				/* Init value of MSTOP2 */
#define CPG_BUS_3_MSTOP_INIT		(0xFFFFFE0CuL)				/* Init value of MSTOP3 */
#define CPG_BUS_4_MSTOP_INIT		(0xFBEF4007uL)				/* Init value of MSTOP4 */
#define CPG_BUS_5_MSTOP_INIT		(0xFFEBFEE0uL)				/* Init value of MSTOP5 */
#define CPG_BUS_6_MSTOP_INIT		(0xFFFFFFFFuL)				/* Init value of MSTOP6 */
#define CPG_BUS_7_MSTOP_INIT		(0x5F835F83uL)				/* Init value of MSTOP7 */
#define CPG_BUS_8_MSTOP_INIT		(0x18FE007CuL)				/* Init value of MSTOP8 */
#define CPG_BUS_9_MSTOP_INIT		(0xFC10F810uL)				/* Init value of MSTOP9 */
#define CPG_BUS_10_MSTOP_INIT		(0xD8BED8AEuL)				/* Init value of MSTOP10 */
#define CPG_BUS_11_MSTOP_INIT		(0xFFFFFFFFuL)				/* Init value of MSTOP11 */
#define CPG_BUS_12_MSTOP_INIT		(0x06030201uL)				/* Init value of MSTOP12 */
#define CPG_BUS_13_MSTOP_INIT		(0x07FF07FFuL)				/* Init value of MSTOP13 */


/*** CPG_CDDIV1 ***/
#define CPG_CDDIV1_DIVCTL0WEN		(0x00010000uL)				/* write enable for DIVCTL0 */
#define CPG_CDDIV1_DIVCTL0_DIV1 	(0x00000000uL)				/* PLLCA55_0_GEAR (0:1/1) */
#define CPG_CDDIV1_DIVCTL0_DIV2 	(0x00000001uL)				/* PLLCA55_0_GEAR (0:1/2) */
#define CPG_CDDIV1_DIVCTL0_DIV4 	(0x00000002uL)				/* PLLCA55_0_GEAR (0:1/4) */
#define CPG_CDDIV1_DIVCTL0_DIV8 	(0x00000003uL)				/* PLLCA55_0_GEAR (0:1/8) */

/*** CPG_SSEL1 ***/
#define CPG_SSEL1_SELCTL2WEN		(0x01000000uL)				/* write enable for SELCTL2 */
#define CPG_SSEL1_SELCTL3WEN		(0x10000000uL)				/* write enable for SELCTL3 */
#define CPG_SSEL1_SELCTL2_MASK		(0x00000100uL)				/* SMUX2_XSPI_CLK0 mask */
#define CPG_SSEL1_SELCTL2_CLK533	(0x00000000uL)				/* SMUX2_XSPI_CLK0 (0:CDIV3_CLK533_PLLCM33_FIX) */
#define CPG_SSEL1_SELCTL2_CLK400	(0x00000100uL)				/* SMUX2_XSPI_CLK0 (1:CDIV4_CLK400_PLLCM33_FIX) */
#define CPG_SSEL1_SELCTL3_MASK		(0x00001000uL)				/* SMUX2_XSPI_CLK1 mask */
#define CPG_SSEL1_SELCTL3_XSPI_CLK0 (0x00000000uL)				/* SMUX2_XSPI_CLK1 (0:SMUX2_XSPI_CLK0) */
#define CPG_SSEL1_SELCTL3_CLK320	(0x00001000uL)				/* SMUX2_XSPI_CLK1 (1:CDIV5_CLK320_PLLCM33_FIX) */

/*** CPG_CSDIV0 ***/
#define CPG_CSDIV0_DIVCTL3WEN		(0x10000000uL)				/* write enable for DIVCTL3 */
#define CPG_CSDIV0_DIVCTL3_MASK 	(0x00003000uL)				/* PLLCM33_XSPI_GEAR:CSDIV_2to16_PLLCM33_XSPI mask */
#define CPG_CSDIV0_DIVCTL3_DIV2 	(0x00000000uL)				/* PLLCM33_XSPI_GEAR:CSDIV_2to16_PLLCM33_XSPI (0:1/2) */
#define CPG_CSDIV0_DIVCTL3_DIV4 	(0x00001000uL)				/* PLLCM33_XSPI_GEAR:CSDIV_2to16_PLLCM33_XSPI (1:1/4) */
#define CPG_CSDIV0_DIVCTL3_DIV8 	(0x00002000uL)				/* PLLCM33_XSPI_GEAR:CSDIV_2to16_PLLCM33_XSPI (2:1/8) */
#define CPG_CSDIV0_DIVCTL3_DIV16	(0x00003000uL)				/* PLLCM33_XSPI_GEAR:CSDIV_2to16_PLLCM33_XSPI (3:1/16) */

/*** Bit define of CPG_REG_CLKON4/CPG_REG_CLKMON2 register ***/
#define CPG_CLKON_ACPU_OSTM0_WEN	(0x00200000uL)				/* Write-enable to clock register */
#define CPG_CLKON_ACPU_OSTM0_ON 	(0x00000020uL)				/* OSTM0_PCLK on */
#define CPG_CLKON_ACPU_OSTM0_OFF	(0x00000000uL)				/* OSTM0_PCLK off */
#define CPG_CLKMON_ACPU_OSTM0_MASK	(0x00000020uL)				/* Monitor clock mask for OSTM0 */
#define CPG_CLKMON_ACPU_OSTM0_ON	(0x00000020uL)				/* Monitor clock on for OSTM0 */
#define CPG_CLKMON_ACPU_OSTM0_OFF	(0x00000000uL)				/* Monitor clock off for OSTM0 */

/*** Bit define of CPG_REG_RST6/CPG_REG_RSTMON3 register ***/
#define CPG_RSTON_ACPU_OSTM0_WEN	(0x80000000uL)				/* Write-enable to reset register */
#define CPG_RSTON_ACPU_OSTM0_OFF	(0x00008000uL)				/* Reset off for OSTM0 */
#define CPG_RSTON_ACPU_OSTM0_ON 	(0x00000000uL)				/* Reset on  for OSTM0 */
#define CPG_RSTMON_ACPU_OSTM0_MASK	(0x00000001uL)				/* Monitor reset mask for OSTM0 */
#define CPG_RSTMON_ACPU_OSTM0_ON	(0x00000001uL)				/* Monitor reset on for OSTM0 */
#define CPG_RSTMON_ACPU_OSTM0_OFF	(0x00000000uL)				/* Monitor reset off for OSTM0 */

/*** Bit define of CPG_REG_CLKON4/CPG_REG_CLKMON2 register ***/
#define CPG_CLKON_MCPU_OSTM0_WEN	(0x00080000uL)				/* Write-enable to clock register */
#define CPG_CLKON_MCPU_OSTM0_ON 	(0x00000008uL)				/* OSTM0_PCLK on */
#define CPG_CLKON_MCPU_OSTM0_OFF	(0x00000000uL)				/* OSTM0_PCLK off */
#define CPG_CLKMON_MCPU_OSTM0_MASK	(0x00000008uL)				/* Monitor clock mask for OSTM0 */
#define CPG_CLKMON_MCPU_OSTM0_ON	(0x00000008uL)				/* Monitor clock on for OSTM0 */
#define CPG_CLKMON_MCPU_OSTM0_OFF	(0x00000000uL)				/* Monitor clock off for OSTM0 */

/*** Bit define of CPG_REG_RST6/CPG_REG_RSTMON2 register ***/
#define CPG_RSTON_MCPU_OSTM0_WEN	(0x20000000uL)				/* Write-enable to reset register */
#define CPG_RSTON_MCPU_OSTM0_OFF	(0x00002000uL)				/* Reset off for OSTM0 */
#define CPG_RSTON_MCPU_OSTM0_ON 	(0x00000000uL)				/* Reset on  for OSTM0 */
#define CPG_RSTMON_MCPU_OSTM0_MASK	(0x40000000uL)				/* Monitor reset mask for OSTM0 */
#define CPG_RSTMON_MCPU_OSTM0_ON	(0x40000000uL)				/* Monitor reset on for OSTM0 */
#define CPG_RSTMON_MCPU_OSTM0_OFF	(0x00000000uL)				/* Monitor reset off for OSTM0 */

/*** Bit define of CPG_REG_CLKON10/CPG_REG_CLKMON5 register ***/
#define CPG_CLKON_SPI0_WEN			(0x00070000uL)				/* Write-enable to clock register */
#define CPG_CLKON_SPI0_ON			(0x00000007uL)				/* SPI_CLK0 and SPI_ACLK on */
#define CPG_CLKON_SPI0_OFF			(0x00000000uL)				/* SPI_CLK0 and SPI_ACLK off */
#define CPG_CLKMON_SPI0_MASK		(0x00000007uL)				/* Monitor clock mask for SPI_CLK0 */
#define CPG_CLKMON_SPI0_ON			(0x00000007uL)				/* Monitor clock on for SPI_CLK0 */
#define CPG_CLKMON_SPI0_OFF 		(0x00000000uL)				/* Monitor clock off for SPI_CLK0 */

/*** Bit define of CPG_REG_CLKON9/CPG_REG_CLKMON4 register ***/
#define CPG_CLKON_SPI0_HCLK_WEN 	(0x80000000uL)				/* Write-enable to clock register */
#define CPG_CLKON_SPI0_HCLK_ON		(0x00008000uL)				/* SPI_HCLK on */
#define CPG_CLKON_SPI0_HCLK_OFF 	(0x00000000uL)				/* SPI_HCLK off */
#define CPG_CLKMON_SPI0_HCLK_MASK	(0x80000000uL)				/* Monitor clock mask for SPI_HCLK */
#define CPG_CLKMON_SPI0_HCLK_ON 	(0x80000000uL)				/* Monitor clock on for SPI_HCLK */
#define CPG_CLKMON_SPI0_HCLK_OFF	(0x00000000uL)				/* Monitor clock off for SPI_HCLK */

/*** Bit define of CPG_REG_RST10/CPG_REG_RSTMON4 register ***/
#define CPG_RSTON_SPI0_WEN			(0x00180000uL)				/* Write-enable to reset register */
#define CPG_RSTON_SPI0_OFF			(0x00000018uL)				/* Reset off for SPI0 */
#define CPG_RSTON_SPI0_ON			(0x00000000uL)				/* Reset on  for SPI0 */
#define CPG_RSTMON_SPI0_MASK		(0x00300000uL)				/* Monitor reset mask for SPI0 */
#define CPG_RSTMON_SPI0_ON			(0x00300000uL)				/* Monitor reset on for SPI0 */
#define CPG_RSTMON_SPI0_OFF 		(0x00000000uL)				/* Monitor reset off for SPI0 */

/*** Bit define of CPG_REG_CLKON10/CPG_REG_CLKMON5 register ***/
#define CPG_CLKON_SDHI0_WEN 		(0x00780000uL)				/* Write-enable to clock register */
#define CPG_CLKON_SDHI0_ON			(0x00000078uL)				/* SDHI0_IMCLK/SDHI0_IMCLK2/SDHI0_CLK_HS/SDHI0_ACLK on */
#define CPG_CLKON_SDHI0_OFF 		(0x00000000uL)				/* SDHI0_IMCLK/SDHI0_IMCLK2/SDHI0_CLK_HS/SDHI0_ACLK off */
#define CPG_CLKMON_SDHI0_MASK		(0x00000078uL)				/* Monitor clock mask for SDHI0 */
#define CPG_CLKMON_SDHI0_ON 		(0x00000078uL)				/* Monitor clock on for SDHI0 */
#define CPG_CLKMON_SDHI0_OFF		(0x00000000uL)				/* Monitor clock off for SDHI0 */

/*** Bit define of CPG_REG_RST10/CPG_REG_RSTMON4 register ***/
#define CPG_RSTON_SDHI0_WEN 		(0x00800000uL)				/* Write-enable to reset register */
#define CPG_RSTON_SDHI0_ON			(0x00000000uL)				/* Reset on for SDHI0 */
#define CPG_RSTON_SDHI0_OFF 		(0x00000080uL)				/* Reset off for SDHI0 */
#define CPG_RSTMON_SDHI0_MASK		(0x01000000uL)				/* Monitor reset mask for SDHI0 */
#define CPG_RSTMON_SDHI0_ON 		(0x01000000uL)				/* Monitor reset on for SDHI0 */
#define CPG_RSTMON_SDHI0_OFF		(0x00000000uL)				/* Monitor reset off for SDHI0 */

/*** Bit define of CPG_REG_CLKON8/CPG_REG_CLKMON4 register ***/
#define CPG_CLKON_SCIF0_WEN 		(0x80000000uL)				/* Write-enable to clock register */
#define CPG_CLKON_SCIF0_ON			(0x00008000uL)				/* clk_pck on */
#define CPG_CLKON_SCIF0_OFF 		(0x00000000uL)				/* clk_pck off */
#define CPG_CLKMON_SCIF0_MASK		(0x00008000uL)				/* Monitor clock mask for SCIF0 */
#define CPG_CLKMON_SCIF0_ON 		(0x00008000uL)				/* Monitor clock on for SCIF0 */
#define CPG_CLKMON_SCIF0_OFF		(0x00000000uL)				/* Monitor clock off for SCIF0 */

/*** Bit define of CPG_REG_RST9/CPG_REG_RSTMON4 register ***/
#define CPG_RSTON_SCIF0_WEN 		(0x00200000uL)				/* Write-enable to reset register */
#define CPG_RSTON_SCIF0_OFF 		(0x00000020uL)				/* Reset off for SCIF0 */
#define CPG_RSTON_SCIF0_ON			(0x00000000uL)				/* Reset on for SCIF0 */
#define CPG_RSTMON_SCIF0_MASK		(0x00000040uL)				/* Monitor reset mask for SCIF0 */
#define CPG_RSTMON_SCIF0_ON 		(0x00000040uL)				/* Monitor reset on for SCIF0 */
#define CPG_RSTMON_SCIF0_OFF		(0x00000000uL)				/* Monitor reset off for SCIF0 */

/*** Bit define of CPG_REG_CLKON26/CPG_REG_CLKMON11 register ***/
#define CPG_CLKON_RSIPG_WEN 				 (0x40000000uL)  /* Write-enable to clock register */
#define CPG_CLKON_RSIPG_ON					 (0x00004000uL)  /* SHIPG_clkb on */
#define CPG_CLKON_RSIPG_OFF 				 (0x00000000uL)  /* SHIPG_clkb off */
#define CPG_CLKMON_RSIPG_MASK				 (0x00000010uL)  /* Monitor clock mask for SHIPG_clkb */
#define CPG_CLKMON_RSIPG_ON 				 (0x00000010uL)  /* Monitor clock on for SHIPG_clkb */
#define CPG_CLKMON_RSIPG_OFF				 (0x00000000uL)  /* Monitor clock off for SHIPG_clkb */

/*** Bit define of CPG_REG_RST18/CPG_REG_RSTMON9 register ***/
#define CPG_RSTON_RSIPG_WEN 				 (0x00080000uL)  /* Write-enable to reset register */
#define CPG_RSTON_RSIPG_OFF 				 (0x00000008uL)  /* Reset off for SHIPG_rst_n */
#define CPG_RSTON_RSIPG_ON					 (0x00000000uL)  /* Reset on for SHIPG_rst_n */
#define CPG_RSTMON_RSIPG_MASK				 (0x00000008uL)  /* Monitor reset mask for SHIPG_rst_n */
#define CPG_RSTMON_RSIPG_ON 				 (0x00000008uL)  /* Monitor reset on for SHIPG_rst_n */
#define CPG_RSTMON_RSIPG_OFF				 (0x00000000uL)  /* Monitor reset off for SHIPG_rst_n */

/*** Bit define of CPG_REG_CLKON11/CPG_REG_CLKMON5 register ***/
#define CPG_CLKON_USB2_WEN					 (0x00F80000uL)  /* Write-enable to clock register */
#define CPG_CLKON_USB2_ON					 (0x000000F8uL)  /* USB2_0_U2H0_HCLK/USB2_0_U2H1_HCLK/USB2_0_U2P_EXR_CPUCLK/USB2_0_PCLK_usbtst0/USB2_0_PCLK_usbtst1 on */
#define CPG_CLKON_USB2_OFF					 (0x00000000uL)  /* USB2_0_U2H0_HCLK/USB2_0_U2H1_HCLK/USB2_0_U2P_EXR_CPUCLK/USB2_0_PCLK_usbtst0/USB2_0_PCLK_usbtst1 off */
#define CPG_CLKMON_USB2_MASK				 (0x00F80000uL)  /* Monitor clock mask for USB2_0_U2H0_HCLK/USB2_0_U2H1_HCLK/USB2_0_U2P_EXR_CPUCLK/USB2_0_PCLK_usbtst0/USB2_0_PCLK_usbtst1 */
#define CPG_CLKMON_USB2_ON					 (0x00F80000uL)  /* Monitor clock on for USB2_0_U2H0_HCLK/USB2_0_U2H1_HCLK/USB2_0_U2P_EXR_CPUCLK/USB2_0_PCLK_usbtst0/USB2_0_PCLK_usbtst1 */
#define CPG_CLKMON_USB2_OFF 				 (0x00000000uL)  /* Monitor clock off for USB2_0_U2H0_HCLK/USB2_0_U2H1_HCLK/USB2_0_U2P_EXR_CPUCLK/USB2_0_PCLK_usbtst0/USB2_0_PCLK_usbtst1 */

/*** Bit define of CPG_REG_RST10/CPG_REG_RSTMON4 register ***/
#define CPG_RSTON_USB2_WEN					 (0x70000000uL)  /* Write-enable to reset register */
#define CPG_RSTON_USB2_OFF					 (0x00007000uL)  /* Reset off for USB2_0_U2H0_HRESETN/USB2_0_U2H1_HRESETN/USB2_0_U2P_EXL_SYSRST */
#define CPG_RSTON_USB2_ON					 (0x00000000uL)  /* Reset off for USB2_0_U2H0_HRESETN/USB2_0_U2H1_HRESETN/USB2_0_U2P_EXL_SYSRST */
#define CPG_RSTMON_USB2_MASK				 (0xE0000000uL)  /* Monitor reset mask for USB2_0_U2H0_HRESETN/USB2_0_U2H1_HRESETN/USB2_0_U2P_EXL_SYSRST */
#define CPG_RSTMON_USB2_ON					 (0xE0000000uL)  /* Monitor reset on for USB2_0_U2H0_HRESETN/USB2_0_U2H1_HRESETN/USB2_0_U2P_EXL_SYSRST */
#define CPG_RSTMON_USB2_OFF 				 (0x00000000uL)  /* Monitor reset off for USB2_0_U2H0_HRESETN/USB2_0_U2H1_HRESETN/USB2_0_U2P_EXL_SYSRST */

/*** Bit define of CPG_REG_RST10/CPG_REG_RSTMON5 register ***/
#define CPG_RSTON_USB2_2_WEN				 (0x80000000uL)  /* Write-enable to reset register */
#define CPG_RSTON_USB2_2_OFF				 (0x00008000uL)  /* Reset off for USB2_0_PRESETN */
#define CPG_RSTON_USB2_2_ON 				 (0x00000000uL)  /* Reset off for USB2_0_PRESETN */
#define CPG_RSTMON_USB2_2_MASK				 (0x00000001uL)  /* Monitor reset mask for USB2_0_PRESETN */
#define CPG_RSTMON_USB2_2_ON				 (0x00000001uL)  /* Monitor reset on for USB2_0_PRESETN */
#define CPG_RSTMON_USB2_2_OFF				 (0x00000000uL)  /* Monitor reset off for USB2_0_PRESETN */

/*** Bit define of MSTOP register ***/
#define CPG_MSTOP2_ACPU_OSTM0		(0x00002000uL)				/* MSTOP bit of ACPU_OSTM0 */
#define CPG_MSTOP3_SCIF 			(0x00004000uL)				/* MSTOP bit of SCIF0 */
#define CPG_MSTOP4_TZC_XSPI 		(0x00000020uL)				/* MSTOP bit of xSPI(TZC-400) */
#define CPG_MSTOP5_XSPI_REG 		(0x00000020uL)				/* MSTOP bit of XSPI_REG */
#define CPG_MSTOP5_MCPU_OSTM0		(0x00000400uL)				/* MSTOP bit of MCPU_OSTM0 */
#define CPG_MSTOP7_USB2 			(0x00000F80uL)				/* MSTOP bit of USB2.0 */
#define CPG_MSTOP8_SD0				(0x00000004uL)				/* MSTOP bit of SD0 */
#define CPG_MSTOP13_SHIPG			(0x00000080uL)				/* MSTOP bit of SHIPG */
#define CPG_MSTOP13_SHIP			(0x00000100uL)				/* MSTOP bit of SHIP */

#define CPG_MSTOP_WEN_SHIFT 		(16)						/* shift count of WEN bits */
#define CPG_MSTOP_MASK				(0x0000FFFFuL)				/* mask value of MSTOP bits */
#endif	/* 1 */
#endif	/* __CPG_REGS_H__ */
