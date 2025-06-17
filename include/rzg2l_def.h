/*
 * Copyright (c) 2020, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RZG2L_DEF_H__
#define __RZG2L_DEF_H__

#define RZG2L_SRAM_BASE				(0x00010000)
#define RZG2L_DEVICE_BASE           (0x10000000)
#define RZG2L_SCIF0_BASE            (0x1004B800)
#define RZG2L_SPIMULT_BASE          (0x10060000)
#define RZG2L_SPIMULT_WBUF_BASE     (0x10070000)
#define RZG2L_SYC_BASE              (0x11000000)
#define RZG2L_CPG_BASE              (0x11010000)
#define RZG2L_SYSC_BASE             (0x11020000)
#define RZG2L_GPIO_BASE             (0x11030000)
#define RZG2L_TZC_SPI_BASE          (0x11060000)
#define RZG2L_TZC_DDR_BASE          (0x11070000)
#define RZG2L_DDR_PHY_BASE          (0x11400000)
#define RZG2L_DDR_MEMC_BASE         (0x11410000)
#define RZG2L_DMAC_S_AXI_BASE       (0x11800000)
#define RZG2L_DMAC_S_APB_BASE       (0x11810000)
#define RZG2L_DMAC_NS_AXI_BASE      (0x11820000)
#define RZG2L_DMAC_NS_APB_BASE      (0x11830000)
#define RZG2L_GIC_BASE              (0x11900000)
#define RZG2L_SD0_BASE              (0x11C00000)
#define RZG2L_WDT_BASE              (0x12800800)
#define RZG2L_SPIROM_BASE           (0x20000000)
#define RZG2L_DDR1_BASE             (0x40000000)
#define RZG2L_DDR2_BASE             (0x80000000)
#define RZG2L_DDR3_BASE             (0x100000000)

#define RZG2L_GICD_BASE             (RZG2L_GIC_BASE)
#define RZG2L_GICR_BASE             (RZG2L_GIC_BASE + 0x00040000)

#define RZG2L_SRAM_SIZE				(0x00030000 - RZG2L_SRAM_BASE)
#define RZG2L_DEVICE_SIZE           (0x15000000 - RZG2L_DEVICE_BASE)
#define RZG2L_SPIROM_SIZE           (0x30000000 - RZG2L_SPIROM_BASE)
#define RZG2L_DDR1_SIZE             (RZG2L_DDR2_BASE - RZG2L_DDR1_BASE)
#define RZG2L_DDR2_SIZE             (RZG2L_DDR3_BASE - RZG2L_DDR2_BASE)

#define RZG2L_SPIROM_FIP_BASE		(RZG2L_SPIROM_BASE + 0x0001D200)
#define RZG2L_SPIROM_FIP_SIZE		(0x30000000 - RZG2L_SPIROM_FIP_BASE)

#define RZG2L_SYC_INCK_HZ           (24000000)
#define RZG2L_UART_INCK_HZ          (100000000)
#define RZG2L_UART_BARDRATE         (115200)

/* Boot Info base address */
#define RZG2L_BOOTINFO_BASE			(RZG2L_SRAM_BASE)

/* Base address where parameters to BL31 are stored */
#define PARAMS_BASE					(RZG2L_SRAM_BASE + 0x0001F000)
#define PARAMS_SIZE					(0x1000)

/* Address offset register for accessing the 34-bit address space */
#define SYS_AOF0                	(0x0C00)      /* SD ch0/ch1 */
#define SYS_AOF1                	(0x0C04)      /* Ether ch0/ch1 */
#define SYS_AOF2                	(0x0C08)      /* USB2 ch0/ch1 Host */
#define SYS_AOF3                	(0x0C0C)      /* USB2 ch0 Function */
#define SYS_AOF4                	(0x0C10)      /* LCDC and DSI */
#define SYS_AOF5                	(0x0C14)      /* H264 */
#define SYS_AOF6                	(0x0C18)      /* Secure/Non-Secure DMAC */

#endif /* __RZG2L_DEF_H__ */
