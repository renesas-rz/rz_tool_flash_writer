/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __RZ_SOC_DEF_H__
#define __RZ_SOC_DEF_H__

#include <lib/utils_def.h>

#define RZG3E_BOOT_ROM_BASE			(0x00000000)
#define RZG3E_SRAM0_BASE			(0x08000000)
#define RZG3E_SRAM1_BASE			(0x08040000)

#define RZG3E_DEVICE_BASE			(0x10000000)

#define RZG3E_ELC					(0x10400000)
#define RZG3E_PFC_BASE				(0x10410000)
#define RZG3E_CPG_BASE				(0x10420000)
#define RZG3E_SYSC_BASE				(0x10430000)

#define RZG3E_OTP_BASE				(0x10450000)
#define RZG3E_TZC400_SRAM_BASE		(0x10460000)
#define RZG3E_TZC400_xSPI_BASE		(0x10470000)
#define RZG3E_MHU_BASE				(0x10480000)

#define RZG3E_XSPI_BASE				(0x11030000)
#define RZG3E_SCIF_BASE				(0x11C01400)

//#define PLAT_ACPU_OSTM0_REG_BASE    (0x14000000)
#define RZG3E_GTM0_BASE				(0x14000000)
#define	RZG3E_WDT_CA55_BASE			(0x14400000)

#define RZG3E_TZC400_DDR_0_BASE		(0x13C60000)
#define RZG3E_TZC400_DDR_1_BASE		(0x13C70000)
#define RZG3E_TZC400_RCPU_BASE		(0x13CA0000)

#define RZG3E_TZC400_PCIe_BASE		(0x13CC0000)

//#define RZG3E_SYC_BASE			(0x14010000)
#define RZG3E_SYC_BASE				(0x10430000)

#define RZG3E_GIC_BASE				(0x14900000)
#define RZG3E_GICD_BASE				(RZG3E_GIC_BASE)
#define RZG3E_GICR_BASE				(RZG3E_GIC_BASE + 0x00040000)

#define RZG3E_SD0_BASE				(0x15C00000)
#define RZG3E_SD1_BASE				(0x15C10000)
#define RZG3E_SD2_BASE				(0x15C20000)

#define RZG3E_DDR_PHY_BASE			(0x1A000000)
#define RZG3E_DDR_MEMC_BASE			(0x1E000000)

#define RZ_SOC_DDR_PHY_BASE			RZG3E_DDR_PHY_BASE
#define RZ_SOC_DDR_MC_BASE			RZG3E_DDR_MEMC_BASE

#define RZ_SOC_DDR_PHY_BASE			RZG3E_DDR_PHY_BASE
#define RZ_SOC_DDR_MC_BASE			RZG3E_DDR_MEMC_BASE

#define RZG3E_XSPI_MEMORY_MAP_BASE	(0x20000000)
#define RZG3E_PCIe_MIRROR_BASE		(0x30000000)
#define RZG3E_DDR_BASE				(0x40000000)
#define RZG3E_PCIe_BASE				(0x440000000)

#define RZG3E_SYC_INCK_HZ			(24000000)
#define RZG3E_UART_INCK_HZ			(100000000)

/* Error Interrupt CM33 Status Register k */
#define RZG3E_ELC_ERINTM33CTL(k)	(RZG3E_ELC + 0x0304 + ((k) * 0x004))

/* Error Interrupt CM33 Status Clear Register k */
#define RZG3E_ELC_ERINTM33CLR(k)	(RZG3E_ELC + 0x0314 + ((k) * 0x004))

/* Error Interrupt CA55 Status Register k */
#define RZG3E_ELC_ERINTA55CTL(k)	(RZG3E_ELC + 0x0338 + ((k) * 0x004))

/* Error Interrupt CA55 Status Clear Register k */
#define RZG3E_ELC_ERINTA55CLR(k)	(RZG3E_ELC + 0x0348 + ((k) * 0x004))

#define RZG3E_UART_BARDRATE			(115200)

#define SYS_BASE					RZG3E_SYSC_BASE
#define PFC_BASE					RZG3E_PFC_BASE
#define CPG_BASE					RZG3E_CPG_BASE
#define XSPI_BASE					RZG3E_XSPI_BASE

/* eMMC registers */
#define MMC0_SD_BASE				RZG3E_SD0_BASE
#define MMC1_SD_BASE				RZG3E_SD1_BASE
#define MMC2_SD_BASE				RZG3E_SD2_BASE

#endif /* __RZ_SOC_DEF_H__ */
