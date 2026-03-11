/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

	.align	4
        LDR x0, =__STACKS_END__
        MOV sp,x0

	/* clear bss section */
	mov	W0, #0x0
	ldr	X1, =__BSS_START__
	ldr	X2, =__BSS_SIZE__
bss_loop:
	subs	X2, X2, #4
	bcc	bss_end
	str	W0, [X1, X2]
	b	bss_loop
bss_end:
	BL	Main
	.end
