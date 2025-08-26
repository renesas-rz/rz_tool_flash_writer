/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : xspi_iodefine.h
 * Version      : 1.0
 * Description  : iodefine header file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.09.2020 1.00     First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef XSPI_IODEFINE_H
#define XSPI_IODEFINE_H

#define XSPI_BASE			   (0x11030000UL)

/******************************* xSPI Registers *******************************/
#define XSPI_WRAPCFG_OFFSET 	(0x000UL)
#define XSPI_COMCFG_OFFSET		(0x004UL)
#define XSPI_BMCFG_OFFSET		(0x008UL)
#define XSPI_CMCFG0CS0_OFFSET	(0x010UL)
#define XSPI_CMCFG1CS0_OFFSET	(0x014UL)
#define XSPI_CMCFG2CS0_OFFSET	(0x018UL)
#define XSPI_LIOCFGCS0_OFFSET	(0x050UL)
#define XSPI_BMCTL0_OFFSET		(0x060UL)
#define XSPI_CSSCTL_OFFSET		(0x06CUL)
#define XSPI_CDCTL0_OFFSET		(0x070UL)
#define XSPI_CDTBUF0_OFFSET 	(0x080UL)
#define XSPI_CDABUF0_OFFSET 	(0x084UL)
#define XSPI_CDD0BUF0_OFFSET	(0x088UL)
#define XSPI_LIOCTL_OFFSET		(0x108UL)
#define XSPI_INTS_OFFSET		(0x190UL)
#define XSPI_INTC_OFFSET		(0x194UL)
#define XSPI_INTE_OFFSET		(0x198UL)

#define XSPI_WRAPCFG(base)		((volatile uint32_t *)((base) + XSPI_WRAPCFG_OFFSET))	   /* xSPI Wrapper Configuration register */
#define XSPI_COMCFG(base)		((volatile uint32_t *)((base) + XSPI_COMCFG_OFFSET))	   /* xSPI Common Configuration register */
#define XSPI_BMCFG(base)		((volatile uint32_t *)((base) + XSPI_BMCFG_OFFSET)) 	   /* xSPI Bridge Map Configuration register */
#define XSPI_CMCFG0CS0(base)	((volatile uint32_t *)((base) + XSPI_CMCFG0CS0_OFFSET))    /* xSPI Command Map Configuration register 0 cs0 */
#define XSPI_CMCFG1CS0(base)	((volatile uint32_t *)((base) + XSPI_CMCFG1CS0_OFFSET))    /* xSPI Command Map Configuration register 1 cs0 */
#define XSPI_CMCFG2CS0(base)	((volatile uint32_t *)((base) + XSPI_CMCFG2CS0_OFFSET))    /* xSPI Command Map Configuration register 2 cs0 */
#define XSPI_LIOCFGCS0(base)	((volatile uint32_t *)((base) + XSPI_LIOCFGCS0_OFFSET))    /* xSPI Link I/O Configuration register cs0 */
#define XSPI_BMCTL0(base)		((volatile uint32_t *)((base) + XSPI_BMCTL0_OFFSET))	   /* xSPI Bridge Map Control register 0 */
#define XSPI_CSSCTL(base)		((volatile uint32_t *)((base) + XSPI_CSSCTL_OFFSET))	   /* xSPI Command Map Control register */
#define XSPI_CDCTL0(base)		((volatile uint32_t *)((base) + XSPI_CDCTL0_OFFSET))	   /* xSPI Command Manual Control register 0 */
#define XSPI_CDTBUF0(base)		((volatile uint32_t *)((base) + XSPI_CDTBUF0_OFFSET))	   /* xSPI Command Manual Type buf - register */
#define XSPI_CDABUF0(base)		((volatile uint32_t *)((base) + XSPI_CDABUF0_OFFSET))	   /* xSPI Command Manual Address buf 0 register */
#define XSPI_CDD0BUF0(base) 	((volatile uint32_t *)((base) + XSPI_CDD0BUF0_OFFSET))	   /* xSPI Command Manual Data 0 buf 0 register */
#define XSPI_LIOCTL(base)		((volatile uint32_t *)((base) + XSPI_LIOCTL_OFFSET))	   /* xSPI Link I/O Control register */
#define XSPI_INTS(base) 		((volatile uint32_t *)((base) + XSPI_INTS_OFFSET))		   /* xSPI Interrupt Status register */
#define XSPI_INTC(base) 		((volatile uint32_t *)((base) + XSPI_INTC_OFFSET))		   /* xSPI Interrupt Clear register */
#define XSPI_INTE(base) 		((volatile uint32_t *)((base) + XSPI_INTE_OFFSET))		   /* xSPI Interrupt Enable register */

/* WRAPCFG register */
#define XSPI_WRAPCFG_CKSFTCS0		(0U)
#define XSPI_WRAPCFG_CKSFTCS0_MSK	(0x1FU << XSPI_WRAPCFG_CKSFTCS0)
#define XSPI_WRAPCFG_DSSFTCS0		(8U)
#define XSPI_WRAPCFG_DSSFTCS0_MSK	(0x1FU << XSPI_WRAPCFG_DSSFTCS0)
#define XSPI_WRAPCFG_DSSFTCS1		(24U)
#define XSPI_WRAPCFG_DSSFTCS1_MSK	(0x1FU << XSPI_WRAPCFG_DSSFTCS1)

/* COMCFG register */
#define XSPI_COMCFG_ARBMD			(0U)
#define XSPI_COMCFG_ARBMD_MSK		(0x3U << XSPI_COMCFG_ARBMD)
#define XSPI_COMCFG_ECSINTOUTEN 	(4U)
#define XSPI_COMCFG_ECSINTOUTEN_MSK (0x3U << XSPI_COMCFG_ECSINTOUTEN)
#define XSPI_COMCFG_OEASTEX 		(16U)
#define XSPI_COMCFG_OEASTEX_MSK 	(0x1U << XSPI_COMCFG_OEASTEX)
#define XSPI_COMCFG_OENEGEX 		(17U)
#define XSPI_COMCFG_OENEGEX_MSK 	(0x1U << XSPI_COMCFG_OENEGEX)

/* BMCFGCHn Register */
#define XSPI_BMCFG_WRMD 			(0U)
#define XSPI_BMCFG_WRMD_MSK 		(0x1U << XSPI_BMCFG_WRMD)
#define XSPI_BMCFG_MWRCOMB			(7U)
#define XSPI_BMCFG_MWRCOMB_MSK		(0x1U << XSPI_BMCFG_MWRCOMB)
#define XSPI_BMCFG_MWRSIZE			(8U)
#define XSPI_BMCFG_MWRSIZE_MSK		(0xFFU << XSPI_BMCFG_MWRSIZE)
#define XSPI_BMCFG_PREEN			(16U)
#define XSPI_BMCFG_PREEN_MSK		(0x1U << XSPI_BMCFG_PREEN)
#define XSPI_BMCFG_CMBTIM			(24U)
#define XSPI_BMCFG_CMBTIM_MSK		(0xFFU << XSPI_BMCFG_CMBTIM)

/* CMCFG0CSN Register */
#define XSPI_CMCFG0CS_FFMT			(0U)
#define XSPI_CMCFG0CS_FFMT_MSK		(0x3U << XSPI_CMCFG0CS_FFMT)
#define XSPI_CMCFG0CS_ADDSIZE		(2U)
#define XSPI_CMCFG0CS_ADDSIZE_MSK	(0x3U << XSPI_CMCFG0CS_ADDSIZE)
#define XSPI_CMCFG0CS_WPBST 		(4U)
#define XSPI_CMCFG0CS_WPBST_MSK 	(0x3U << XSPI_CMCFG0CS_WPBST)
#define XSPI_CMCFG0CS_ARYAM 		(5U)
#define XSPI_CMCFG0CS_ARYAM_MSK 	(0x3U << XSPI_CMCFG0CS_ARYAM)
#define XSPI_CMCFG0CS_ADDRPEN		(16U)
#define XSPI_CMCFG0CS_ADDRPEN_MSK	(0xFFU << XSPI_CMCFG0CS_ADDRPEN)
#define XSPI_CMCFG0CS_ADDRPCD		(24U)
#define XSPI_CMCFG0CS_ADDRPCD_MSK	(0xFFU << XSPI_CMCFG0CS_ADDRPCD)

/* xSPI Protocol Mode */
#define XSPI_LIOCFGCS_PRTMD_1S_1S_1S	(0x0000UL)
#define XSPI_LIOCFGCS_PRTMD_8D_8D_8D	(0x03FFUL)

/* CMCFG1CSn Register */
#define XSPI_CMCFG1CS_RDCMD 		(0U)
#define XSPI_CMCFG1CS_RDCMD_MSK 	(0xFFU << XSPI_CMCFG1CS_RDCMD)
#define XSPI_CMCFG1CS_RDLATE		(16U)
#define XSPI_CMCFG1CS_RDLATE_MSK	(0x1FU << XSPI_CMCFG1CS_RDLATE)

/* CMCFG2CSn Register */
#define XSPI_CMCFG1CS_WRCMD 		(0U)
#define XSPI_CMCFG1CS_WRCMD_MSK 	(0xFFU << XSPI_CMCFG1CS_WRCMD)
#define XSPI_CMCFG1CS_WRLATE		(16U)
#define XSPI_CMCFG1CS_WRLATE_MSK	(0x1FU << XSPI_CMCFG1CS_WRLATE)

/* AIBMCFG0/1/2CHn Register */
#define XSPI_AIBMCFG_ID 			(0U)
#define XSPI_AIBMCFG_ID_MSK 		(0xFFFFU << XSPI_AIBMCFG_ID)
#define XSPI_AIBMCFG_MASK			(16U)
#define XSPI_AIBMCFG_MASK_MSK		(0xFFFFU << XSPI_AIBMCFG_MASK)

/* LIOCFGCSn Register */
#define XSPI_LIOCFGCS_PRTMD 		(0U)
#define XSPI_LIOCFGCS_PRTMD_MSK 	(0x3FFU << XSPI_LIOCFGCS_PRTMD)
#define XSPI_LIOCFGCS_LATEMD		(10U)
#define XSPI_LIOCFGCS_LATEMD_MSK	(0x1U << XSPI_LIOCFGCS_LATEMD)
#define XSPI_LIOCFGCS_WRMSKMD		(11U)
#define XSPI_LIOCFGCS_WRMSKMD_MSK	(0x1U << XSPI_LIOCFGCS_WRMSKMD)
#define XSPI_LIOCFGCS_DDRSMPMD		(15U)
#define XSPI_LIOCFGCS_DDRSMPMD_MSK	(0x1U << XSPI_LIOCFGCS_DDRSMPMD)
#define XSPI_LIOCFGCS_CSMIN 		(16U)
#define XSPI_LIOCFGCS_CSMIN_MSK 	(0xFU << XSPI_LIOCFGCS_CSMIN)
#define XSPI_LIOCFGCS_CSASTEX		(20U)
#define XSPI_LIOCFGCS_CSASTEX_MSK	(0x1U << XSPI_LIOCFGCS_CSASTEX)
#define XSPI_LIOCFGCS_CSNEGEX		(21U)
#define XSPI_LIOCFGCS_CSNEGEX_MSK	(0x1U << XSPI_LIOCFGCS_CSNEGEX)
#define XSPI_LIOCFGCS_SDRDRV		(22U)
#define XSPI_LIOCFGCS_SDRDRV_MSK	(0x1U << XSPI_LIOCFGCS_SDRDRV)
#define XSPI_LIOCFGCS_SDRSMPMD		(23U)
#define XSPI_LIOCFGCS_SDRSMPMD_MSK	(0x1U << XSPI_LIOCFGCS_SDRSMPMD)
#define XSPI_LIOCFGCS_SDRSMPSFT 	(24U)
#define XSPI_LIOCFGCS_SDRSMPSFT_MSK (0xFU << XSPI_LIOCFGCS_SDRSMPSFT)
#define XSPI_LIOCFGCS_DDRSMPEX		(24U)
#define XSPI_LIOCFGCS_DDRSMPEX_MSK	(0xFU << XSPI_LIOCFGCS_DDRSMPEX)

/* ABMCFG Register */
#define XSPI_ABMCFG_ODRMD			(0U)
#define XSPI_ABMCFG_ODRMD_MSK		(0x3U << XSPI_ABMCFG_ODRMD)
#define XSPI_ABMCFG_ODRMD_CHSEL 	(16U)
#define XSPI_ABMCFG_ODRMD_CHSEL_MSK (0xFFFFU << XSPI_ABMCFG_ODRMD_CHSEL)

/* BMCTL0 Register */
#define XSPI_BMCTL0_CS0ACC			(0U)
#define XSPI_BMCTL0_CS0ACC_MSK		(0x3U << XSPI_BMCTL0_CS0ACC)
#define XSPI_BMCTL0_CS1ACC			(2U)
#define XSPI_BMCTL0_CS1ACC_MSK		(0x3U << XSPI_BMCTL0_CS1ACC)
#define XSPI_BMCTL0_CH1CS0ACC		(4U)
#define XSPI_BMCTL0_CH1CS0ACC_MSK	(0x3U << XSPI_BMCTL0_CH1CS0ACC)
#define XSPI_BMCTL0_CH1CS1ACC		(6U)
#define XSPI_BMCTL0_CH1CS1ACC_MSK	(0x3U << XSPI_BMCTL0_CH1CS1ACC)

/* BMCTL1 Register */
#define XSPI_BMCTL1_MWRPUSHCH0		(8U)
#define XSPI_BMCTL1_MWRPUSHCH0_MSK	(00x1U << XSPI_BMCTL1_MWRPUSHCH0)
#define XSPI_BMCTL1_MWRPUSHCH1		(9U)
#define XSPI_BMCTL1_MWRPUSHCH1_MSK	(0x1U << XSPI_BMCTL1_MWRPUSHCH1)
#define XSPI_BMCTL1_PBUFCLRCH0		(10U)
#define XSPI_BMCTL1_PBUFCLRCH0_MSK	(0x1U << XSPI_BMCTL1_PBUFCLRCH0)
#define XSPI_BMCTL1_PBUFCLRCH1		(11U)
#define XSPI_BMCTL1_PBUFCLRCH1_MSK	(0x1U << XSPI_BMCTL1_PBUFCLRCH1)

/* CMCTLCHn Register */
#define XSPI_CMCTL_XIPENCODE		(0U)
#define XSPI_CMCTL_XIPENCODE_MSK	(0xFFU << XSPI_CMCTL_XIPENCODE)
#define XSPI_CMCTL_XIPEXCODE		(8U)
#define XSPI_CMCTL_XIPEXCODE_MSK	(0xFFU << XSPI_CMCTL_XIPEXCODE)
#define XSPI_CMCTL_XIPEN			(16U)
#define XSPI_CMCTL_XIPEN_MSK		(0x1U << XSPI_CMCTL_XIPEN)

/* CDCTL0 Register */
#define XSPI_CDCTL0_TRREQ			(0U)
#define XSPI_CDCTL0_TRREQ_MSK		(0x1U << XSPI_CDCTL0_TRREQ)
#define XSPI_CDCTL0_PERMD			(1U)
#define XSPI_CDCTL0_PERMD_MSK		(0x1U << XSPI_CDCTL0_PERMD)
#define XSPI_CDCTL0_CSSEL			(3U)
#define XSPI_CDCTL0_CSSEL_MSK		(0x1U << XSPI_CDCTL0_CSSEL)
#define XSPI_CDCTL0_TRNUM			(4U)
#define XSPI_CDCTL0_TRNUM_MSK		(3x1U << XSPI_CDCTL0_TRNUM)
#define XSPI_CDCTL0_PERITV			(16U)
#define XSPI_CDCTL0_PERITV_MSK		(0x1FU << XSPI_CDCTL0_PERITV)
#define XSPI_CDCTL0_PERREP			(24U)
#define XSPI_CDCTL0_PERREP_MSK		(0xFU << XSPI_CDCTL0_PERREP)

/* CDCTL1 Register */
#define XSPI_CDCTL1_PEREXP			(0U)
#define XSPI_CDCTL1_PEREXP_MSK		(0xFFFFFFFFU << XSPI_CDCTL1_PEREXP)

/* CDCTL2 Register */
#define XSPI_CDCTL2_PERMSK			(0U)
#define XSPI_CDCTL2_PERMSK_MSK		(0xFFFFFFFFU << XSPI_CDCTL2_PERMSK)

/* CDTBUFn Register */
#define XSPI_CDTBUF_CMDSIZE 		(0U)
#define XSPI_CDTBUF_CMDSIZE_MSK 	(0x3U << XSPI_CDTBUF_CMDSIZE)
#define XSPI_CDTBUF_ADDSIZE 		(2U)
#define XSPI_CDTBUF_ADDSIZE_MSK 	(0x7U << XSPI_CDTBUF_ADDSIZE)
#define XSPI_CDTBUF_DATASIZE		(5U)
#define XSPI_CDTBUF_DATASIZE_MSK	(0xFU << XSPI_CDTBUF_DATASIZE)
#define XSPI_CDTBUF_LATE			(9U)
#define XSPI_CDTBUF_LATE_MSK		(0x1FU << XSPI_CDTBUF_LATE)
#define XSPI_CDTBUF_TRTYPE			(15U)
#define XSPI_CDTBUF_TRTYPE_MSK		(0x1U << XSPI_CDTBUF_TRTYPE)
#define XSPI_CDTBUF_CMD 			(16U)
#define XSPI_CDTBUF_CMD_MSK 		(0xFFFFU << XSPI_CDTBUF_CMD)

/* CDABUFn Register */
#define XSPI_CDABUF_ADD 			(0U)
#define XSPI_CDABUF_ADD_MSK 		(0xFFFFFFFFU << XSPI_CDABUF_ADD)

/* CDD0BUFn Register */
#define XSPI_CDD0BUF_DATA			(0U)
#define XSPI_CDD0BUF_DATA_MSK		(0xFFFFFFFFU << XSPI_CDD0BUF_DATA)

/* CDD1BUFn Register */
#define XSPI_CDD1BUF_DATA			(0U)
#define XSPI_CDD1BUF_DATA_MSK		(0xFFFFFFFFU << XSPI_CDD1BUF_DATA)

/* LPCTL0 Register */
#define XSPI_LPCTL0_PATREQ			(0U)
#define XSPI_LPCTL0_PATREQ_MSK		(0x1U << XSPI_LPCTL0_PATREQ)
#define XSPI_LPCTL0_CSSEL			(3U)
#define XSPI_LPCTL0_CSSEL_MSK		(0x1U << XSPI_LPCTL0_CSSEL)
#define XSPI_LPCTL0_XDPIN			(4U)
#define XSPI_LPCTL0_XDPIN_MSK		(0x3U << XSPI_LPCTL0_XDPIN)
#define XSPI_LPCTL0_XD1LEN			(16U)
#define XSPI_LPCTL0_XD1LEN_MSK		(0x1FU << XSPI_LPCTL0_XD1LEN)
#define XSPI_LPCTL0_XD1VAL			(23U)
#define XSPI_LPCTL0_XD1VAL_MSK		(0x1U << XSPI_LPCTL0_XD1VAL)
#define XSPI_LPCTL0_XD2LEN			(24U)
#define XSPI_LPCTL0_XD2LEN_MSK		(0x1FU << XSPI_LPCTL0_XD2LEN)
#define XSPI_LPCTL0_XD2VAL			(31U)
#define XSPI_LPCTL0_XD2VAL_MSK		(0x1U << XSPI_LPCTL0_XD2VAL)

/* LPCTL1 Register */
#define XSPI_LPCTL1_PATREQ			(0U)
#define XSPI_LPCTL1_PATREQ_MSK		(0x3U << XSPI_LPCTL1_PATREQ)
#define XSPI_LPCTL1_CSSEL			(3U)
#define XSPI_LPCTL1_CSSEL_MSK		(0x1U << XSPI_LPCTL1_CSSEL)
#define XSPI_LPCTL1_RSTREP			(4U)
#define XSPI_LPCTL1_RSTREP_MSK		(0x3U << XSPI_LPCTL1_RSTREP)
#define XSPI_LPCTL1_RSTWID			(8U)
#define XSPI_LPCTL1_RSTWID_MSK		(0x7U << XSPI_LPCTL1_RSTWID)
#define XSPI_LPCTL1_RSTSU			(12U)
#define XSPI_LPCTL1_RSTSU_MSK		(0x7U << XSPI_LPCTL1_RSTSU)

/* LIOCTL Register */
#define XSPI_LIOCTL_WPCS0			(0U)
#define XSPI_LIOCTL_WPCS0_MSK		(0x1U << XSPI_LIOCTL_WPCS0)
#define XSPI_LIOCTL_WPCS1			(1U)
#define XSPI_LIOCTL_WPCS1_MSK		(0x1U << XSPI_LIOCTL_WPCS1)
#define XSPI_LIOCTL_RSTCS0			(16U)
#define XSPI_LIOCTL_RSTCS0_MSK		(0x1U << XSPI_LIOCTL_RSTCS0)
#define XSPI_LIOCTL_RSTCS1			(17U)
#define XSPI_LIOCTL_RSTCS1_MSK		(0x1U << XSPI_LIOCTL_RSTCS1)

/* CCCTL0 Register */
#define XSPI_CCCTL0_CAEN			(0U)
#define XSPI_CCCTL0_CAEN_MSK		(0x1U << XSPI_CCCTL0_CAEN)
#define XSPI_CCCTL0_CANOWR			(1U)
#define XSPI_CCCTL0_CANOWR_MSK		(0x1U << XSPI_CCCTL0_CANOWR)
#define XSPI_CCCTL0_CAITV			(8U)
#define XSPI_CCCTL0_CAITV_MSK		(0x1FU << XSPI_CCCTL0_CAITV)
#define XSPI_CCCTL0_CASFTSTA		(16U)
#define XSPI_CCCTL0_CASFTSTA_MSK	(0x1FU << XSPI_CCCTL0_CAITV)
#define XSPI_CCCTL0_CASFTEND		(24U)
#define XSPI_CCCTL0_CASFTEND_MSK	(0x1U << XSPI_CCCTL0_CANOWR)

/* CCCTL1 Register */
#define XSPI_CCCTL1_CACMDSIZE		(0U)
#define XSPI_CCCTL1_CACMDSIZE_MSK	(0x3U << XSPI_CCCTL1_CACMDSIZE)
#define XSPI_CCCTL1_CAADDSIZE		(2U)
#define XSPI_CCCTL1_CAADDSIZE_MSK	(0x7U << XSPI_CCCTL1_CAADDSIZE)
#define XSPI_CCCTL1_CADATASIZE		(5U)
#define XSPI_CCCTL1_CADATASIZE_MSK	(0xFU << XSPI_CCCTL1_CADATASIZE)
#define XSPI_CCCTL1_CAWRLATE		(16U)
#define XSPI_CCCTL1_CAWRLATE_MSK	(0x1FU << XSPI_CCCTL1_CAWRLATE)
#define XSPI_CCCTL1_CARDLATE		(24U)
#define XSPI_CCCTL1_CARDLATE_MSK	(0xFU << XSPI_CCCTL1_CARDLATE)

/* CCCTL2 Register */
#define XSPI_CCCTL2_CAWRCMD 		(0U)
#define XSPI_CCCTL2_CAWRCMD_MSK 	(0xFFFFU << XSPI_CCCTL2_CAWRCMD)
#define XSPI_CCCTL2_CARDCMD 		(16U)
#define XSPI_CCCTL2_CARDCMD_MSK 	(0xFFFFU << XSPI_CCCTL2_CARDCMD)

/* CCCTL3 Register */
#define XSPI_CCCTL3_CAADD			(0U)
#define XSPI_CCCTL3_CAADD_MSK		(0xFFFFFFFFU << XSPI_CCCTL3_CAADD)

/* CCCTL4 Register */
#define XSPI_CCCTL4_CADATA			(0U)
#define XSPI_CCCTL4_CADATA_MSK		(0xFFFFFFFFU << XSPI_CCCTL4_CADATA) 
#define XSPI_CCCTL5_CADATA			(0U)
#define XSPI_CCCTL5_CADATA_MSK		(0xFFFFFFFFU << XSPI_CCCTL5_CADATA) 
#define XSPI_CCCTL6_CADATA			(0U)
#define XSPI_CCCTL6_CADATA_MSK		(0xFFFFFFFFU << XSPI_CCCTL6_CADATA) 

/* COMSTT Register */
#define XSPI_COMSTT_MEMACCCH0		(0U)
#define XSPI_COMSTT_MEMACCCH0_MSK	(0x1U << XSPI_COMSTT_MEMACCCH0)
#define XSPI_COMSTT_MEMACCCH1		(1U)
#define XSPI_COMSTT_MEMACCCH1_MSK	(0x1U << XSPI_COMSTT_MEMACCCH1)
#define XSPI_COMSTT_PBUFNECH0		(4U)
#define XSPI_COMSTT_PBUFNECH0_MSK	(0x1U << XSPI_COMSTT_PBUFNECH0)
#define XSPI_COMSTT_PBUFNECH1		(5U)
#define XSPI_COMSTT_PBUFNECH1_MSK	(0x1U << XSPI_COMSTT_PBUFNECH1)
#define XSPI_COMSTT_WRBUFNECH0		(6U)
#define XSPI_COMSTT_WRBUFNECH0_MSK	(0x1U << XSPI_COMSTT_WRBUFNECH0)
#define XSPI_COMSTT_WRBUFNECH1		(7U)
#define XSPI_COMSTT_WRBUFNECH1_MSK	(0x1U << XSPI_COMSTT_WRBUFNECH1)
#define XSPI_COMSTT_ECSCS0			(16U)
#define XSPI_COMSTT_ECSCS0_MSK		(0x1U << XSPI_COMSTT_ECSCS0)
#define XSPI_COMSTT_INTCS0			(17U)
#define XSPI_COMSTT_INTCS0_MSK		(0x1U << XSPI_COMSTT_INTCS0)
#define XSPI_COMSTT_RSTOCS0 		(17U)
#define XSPI_COMSTT_RSTOCS0_MSK 	(0x1U << XSPI_COMSTT_RSTOCS0)
#define XSPI_COMSTT_ECSCS1			(20U)
#define XSPI_COMSTT_ECSCS1_MSK		(0x1U << XSPI_COMSTT_ECSCS1)
#define XSPI_COMSTT_INTCS1			(21U)
#define XSPI_COMSTT_INTCS1_MSK		(0x1U << XSPI_COMSTT_INTCS1)
#define XSPI_COMSTT_RSTOCS1 		(22U)
#define XSPI_COMSTT_RSTOCS1_MSK 	(0x1U << XSPI_COMSTT_RSTOCS1)

/* CASTT Register */
#define XSPI_COMSTT_CASUC			(0U)
#define XSPI_COMSTT_CASUC_MSK		(0xFFFFFFFFU << XSPI_COMSTT_CASUC)

/* INTS Register */
#define XSPI_INTS_CMDCMP		(0U)
#define XSPI_INTS_CMDCMP_MSK	(0x1U << XSPI_INTS_CMDCMP)
#define XSPI_INTS_PATCMP		(1U)
#define XSPI_INTS_PATCMP_MSK	(0x1U << XSPI_INTS_PATCMP)
#define XSPI_INTS_INICMP		(2U)
#define XSPI_INTS_INICMP_MSK	(0x1U << XSPI_INTS_INICMP)
#define XSPI_INTS_PERTO 		(3U)
#define XSPI_INTS_PERTO_MSK 	(0x1U << XSPI_INTS_PERTO)
#define XSPI_INTS_DSTOCS0		(4U)
#define XSPI_INTS_DSTOCS0_MSK	(0x1U << XSPI_INTS_DSTOCS0)
#define XSPI_INTS_DSTOCS1		(5U)
#define XSPI_INTS_DSTOCS1_MSK	(0x1U << XSPI_INTS_DSTOCS1)
#define XSPI_INTS_ECSCS0		(8U)
#define XSPI_INTS_ECSCS0_MSK	(0x1U << XSPI_INTS_ECSCS0)
#define XSPI_INTS_ECSCS1		(9U)
#define XSPI_INTS_ECSCS1_MSK	(0x1U << XSPI_INTS_ECSCS1)
#define XSPI_INTS_INTCS0		(12U)
#define XSPI_INTS_INTCS0_MSK	(0x1U << XSPI_INTS_INTCS0)
#define XSPI_INTS_INTCS1		(13U)
#define XSPI_INTS_INTCS1_MSK	(0x1U << XSPI_INTS_INTCS1)
#define XSPI_INTS_BRGOFCH0		(16U)
#define XSPI_INTS_BRGOFCH0_MSK	(0x1U << XSPI_INTS_BRGOFCH0)
#define XSPI_INTS_BRGOFCH1		(17U)
#define XSPI_INTS_BRGOFCH1_MSK	(0x1U << XSPI_INTS_BRGOFCH1)
#define XSPI_INTS_BRGUFCH0		(18U)
#define XSPI_INTS_BRGUFCH0_MSK	(0x1U << XSPI_INTS_BRGUFCH0)
#define XSPI_INTS_BRGUFCH1		(19U)
#define XSPI_INTS_BRGUFCH1_MSK	(0x1U << XSPI_INTS_BRGUFCH1)
#define XSPI_INTS_BUSERRCH0 	(20U)
#define XSPI_INTS_BUSERRCH0_MSK (0x1U << XSPI_INTS_BUSERRCH0)
#define XSPI_INTS_BUSERRCH1 	(21U)
#define XSPI_INTS_BUSERRCH1_MSK (0x1U << XSPI_INTS_BUSERRCH1)
#define XSPI_INTS_CAFAILCS0 	(28U)
#define XSPI_INTS_CAFAILCS0_MSK (0x1U << XSPI_INTS_CAFAILCS0)
#define XSPI_INTS_CAFAILCS1 	(29U)
#define XSPI_INTS_CAFAILCS1_MSK (0x1U << XSPI_INTS_CAFAILCS1)
#define XSPI_INTS_CASUCCS0		(30U)
#define XSPI_INTS_CASUCCS0_MSK	(0x1U << XSPI_INTS_CASUCCS0)
#define XSPI_INTS_CASUCCS1		(31U)
#define XSPI_INTS_CASUCCS1_MSK	(0x1U << XSPI_INTS_CASUCCS1)

/* INTC Register */
#define XSPI_INTC_CMDCMPC		(0U)
#define XSPI_INTC_CMDCMPC_MSK	(0x1U << XSPI_INTC_CMDCMPC)
#define XSPI_INTC_PATCMP		(1U)
#define XSPI_INTC_PATCMP_MSK	(0x1U << XSPI_INTC_PATCMP)
#define XSPI_INTC_INICMP		(2U)
#define XSPI_INTC_INICMP_MSK	(0x1U << XSPI_INTC_INICMP)
#define XSPI_INTC_PERTO 		(3U)
#define XSPI_INTC_PERTO_MSK 	(0x1U << XSPI_INTC_PERTO)
#define XSPI_INTC_DSTOCS0		(4U)
#define XSPI_INTC_DSTOCS0_MSK	(0x1U << XSPI_INTC_DSTOCS0)
#define XSPI_INTC_DSTOCS1		(5U)
#define XSPI_INTC_DSTOCS1_MSK	(0x1U << XSPI_INTC_DSTOCS1)
#define XSPI_INTC_ECSCS0		(8U)
#define XSPI_INTC_ECSCS0_MSK	(0x1U << XSPI_INTC_ECSCS0)
#define XSPI_INTC_ECSCS1		(9U)
#define XSPI_INTC_ECSCS1_MSK	(0x1U << XSPI_INTC_ECSCS1)
#define XSPI_INTC_INTCS0		(12U)
#define XSPI_INTC_INTCS0_MSK	(0x1U << XSPI_INTC_INTCS0)
#define XSPI_INTC_INTCS1		(13U)
#define XSPI_INTC_INTCS1_MSK	(0x1U << XSPI_INTC_INTCS1)
#define XSPI_INTC_BRGOFCH0		(16U)
#define XSPI_INTC_BRGOFCH0_MSK	(0x1U << XSPI_INTC_BRGOFCH0)
#define XSPI_INTC_BRGOFCH1		(17U)
#define XSPI_INTC_BRGOFCH1_MSK	(0x1U << XSPI_INTC_BRGOFCH1)
#define XSPI_INTC_BRGUFCH0		(18U)
#define XSPI_INTC_BRGUFCH0_MSK	(0x1U << XSPI_INTC_BRGUFCH0)
#define XSPI_INTC_BRGUFCH1		(19U)
#define XSPI_INTC_BRGUFCH1_MSK	(0x1U << XSPI_INTC_BRGUFCH1)
#define XSPI_INTC_BUSERRCH0 	(20U)
#define XSPI_INTC_BUSERRCH0_MSK (0x1U << XSPI_INTC_BUSERRCH0)
#define XSPI_INTC_BUSERRCH1 	(21U)
#define XSPI_INTC_BUSERRCH1_MSK (0x1U << XSPI_INTC_BUSERRCH1)
#define XSPI_INTC_CAFAILCS0 	(28U)
#define XSPI_INTC_CAFAILCS0_MSK (0x1U << XSPI_INTC_CAFAILCS0)
#define XSPI_INTC_CAFAILCS1 	(29U)
#define XSPI_INTC_CAFAILCS1_MSK (0x1U << XSPI_INTC_CAFAILCS1)
#define XSPI_INTC_CASUCCS0		(30U)
#define XSPI_INTC_CASUCCS0_MSK	(0x1U << XSPI_INTC_CASUCCS0)
#define XSPI_INTC_CASUCCS1		(31U)
#define XSPI_INTC_CASUCCS1_MSK	(0x1U << XSPI_INTC_CASUCCS1)

/* INTE Register */
#define XSPI_INTE_CMDCMPC		(0U)
#define XSPI_INTE_CMDCMPC_MSK	(0x1U << XSPI_INTE_CMDCMPC)
#define XSPI_INTE_PATCMP		(1U)
#define XSPI_INTE_PATCMP_MSK	(0x1U << XSPI_INTE_PATCMP)
#define XSPI_INTE_INICMP		(2U)
#define XSPI_INTE_INICMP_MSK	(0x1U << XSPI_INTE_INICMP)
#define XSPI_INTE_PERTO 		(3U)
#define XSPI_INTE_PERTO_MSK 	(0x1U << XSPI_INTE_PERTO)
#define XSPI_INTE_DSTOCS0		(4U)
#define XSPI_INTE_DSTOCS0_MSK	(0x1U << XSPI_INTE_DSTOCS0)
#define XSPI_INTE_DSTOCS1		(5U)
#define XSPI_INTE_DSTOCS1_MSK	(0x1U << XSPI_INTE_DSTOCS1)
#define XSPI_INTE_ECSCS0		(8U)
#define XSPI_INTE_ECSCS0_MSK	(0x1U << XSPI_INTE_ECSCS0)
#define XSPI_INTE_ECSCS1		(9U)
#define XSPI_INTE_ECSCS1_MSK	(0x1U << XSPI_INTE_ECSCS1)
#define XSPI_INTE_INTCS0		(12U)
#define XSPI_INTE_INTCS0_MSK	(0x1U << XSPI_INTE_INTCS0)
#define XSPI_INTE_INTCS1		(13U)
#define XSPI_INTE_INTCS1_MSK	(0x1U << XSPI_INTE_INTCS1)
#define XSPI_INTE_BRGOFCH0		(16U)
#define XSPI_INTE_BRGOFCH0_MSK	(0x1U << XSPI_INTE_BRGOFCH0)
#define XSPI_INTE_BRGOFCH1		(17U)
#define XSPI_INTE_BRGOFCH1_MSK	(0x1U << XSPI_INTE_BRGOFCH1)
#define XSPI_INTE_BRGUFCH0		(18U)
#define XSPI_INTE_BRGUFCH0_MSK	(0x1U << XSPI_INTE_BRGUFCH0)
#define XSPI_INTE_BRGUFCH1		(19U)
#define XSPI_INTE_BRGUFCH1_MSK	(0x1U << XSPI_INTE_BRGUFCH1)
#define XSPI_INTE_BUSERRCH0 	(20U)
#define XSPI_INTE_BUSERRCH0_MSK (0x1U << XSPI_INTE_BUSERRCH0)
#define XSPI_INTE_BUSERRCH1 	(21U)
#define XSPI_INTE_BUSERRCH1_MSK (0x1U << XSPI_INTE_BUSERRCH1)
#define XSPI_INTE_CAFAILCS0 	(28U)
#define XSPI_INTE_CAFAILCS0_MSK (0x1U << XSPI_INTE_CAFAILCS0)
#define XSPI_INTE_CAFAILCS1 	(29U)
#define XSPI_INTE_CAFAILCS1_MSK (0x1U << XSPI_INTE_CAFAILCS1)
#define XSPI_INTE_CASUCCS0		(30U)
#define XSPI_INTE_CASUCCS0_MSK	(0x1U << XSPI_INTE_CASUCCS0)
#define XSPI_INTE_CASUCCS1		(31U)
#define XSPI_INTE_CASUCCS1_MSK	(0x1U << XSPI_INTE_CASUCCS1)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif /* XSPI_IODEFINE_H */
