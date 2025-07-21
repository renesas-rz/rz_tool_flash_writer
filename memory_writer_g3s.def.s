/*
 * Copyright (c) 2015-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

MEMORY {
	CERT (rwxa): ORIGIN = 0x000A1E00, LENGTH = 0x00000200
	RAM  (rwxa): ORIGIN = 0x000A2000, LENGTH = 0x0002E000
	RAM2 (rwxa): ORIGIN = 0x000D0000, LENGTH = 0x00029000
}

SECTIONS
{
	.cert : {
		. = 0x00000000;
		LONG(__LOAD_SIZE__)
		FILL(0xFF)
		. = 0x00000010;
		LONG(0x00000200)
		. = 0x00000020;
		LONG(0x000A2000)
		. = 0x000001FC;
		LONG(0xAA55FFFF)
	} > CERT

	.text : {
		__RO_START__ = .;
		*(.text*)
		*(.rodata*)
		. = NEXT(64);
		__RO_END__ = .;
	} > RAM

	.data : {
		__DATA_START__ = .;
		 *(.data)
		. = NEXT(64);
		__DATA_END__ = .;
	} > RAM

	__DATA_SIZE__ = SIZEOF(.data);

	__LOAD_SIZE__ = __DATA_END__ - __RO_START__;

	.bss : {
		__BSS_START__ = .;
		 *(.bss)
		 *(COMMON)
		 . = NEXT(64);
		__BSS_END__ = .;
	} > RAM2

	stacks (NOLOAD) : ALIGN(64) {
		__STACKS_START__ = .;
		KEEP(*(writer_stack))
		__STACKS_END__ = .;
	} > RAM2

	__BSS_SIZE__ = SIZEOF(.bss);
}
