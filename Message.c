/*
 * Copyright (c) 2015-2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "dgtable.h"
/**********************
*  TITLE              *
***********************/

const char *const AllHelpMess[ALL_HELP_MESS_LINE] = {
#if SERIAL_FLASH == 1
				"        SPI Flash write command",
				" XCS            erase program to SPI Flash",
				" XLS2           write program to SPI Flash",
				" XLS3           write program to SPI Flash(Binary)",
				"",
#endif /* SERIAL_FLASH == 1 */
#if EMMC == 1
				"        eMMC write command",
				" EM_DCID        display register CID",
				" EM_DCSD        display register CSD",
				" EM_DECSD       display register EXT_CSD",
				" EM_SECSD       change register EXT_CSD byte",
				" EM_W           write program to eMMC",
				" EM_WB          write program to eMMC (Binary)",
				" EM_E           erase program to eMMC",
				"",
#endif /* EMMC == 1 */
#if INTERNAL_MEMORY_ONLY == 0
				"        Load DDR parameters",
				" DDRP           Store DDR parameters into internal SRAM",
				"",
				"        Stress checker command",
				" DDR_S  [sadr] [eadr] {loop}        Simple write-then-read checking of DDR",
				" DDR_RB [sadr] [eadr] {loop}        Random data write-then-read checking of DDR",
				" DDR_FB [sadr] [eadr] [data] {loop} Fixed data write-then-read checking of DDR",
				"",
#endif /* INTERNAL_MEMORY_ONLY == 0 */
				" SUP            Scif speed UP (Change to speed up baud rate setting)",
				" SUD            Scif speed DOWN (Change to speed down baud rate setting)",
				" RESET          Perform RESET of the CPU",
				" H              help",
				" D  {sadr {eadr}}          memory dump  (DM sets dump size)",
				" DM {B|W|L|X}              set&disp dump mode",
				" M  [adr]                  set memory(BYTE)",
				" MW [adr]                  set memory(WORD)",
				" ML [adr]                  set memory(LONG)",
				" MX [adr]                  set memory(LONG LONG)",
				" F  [sadr] [eadr] [data]   fill memory",
				" FL [sadr] [eadr] [data]   fill memory(LONG)",
				" FX [sadr] [eadr] [data]   fill memory(LONG LONG)",
				MESSAGE_END,
};
