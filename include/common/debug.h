/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DEBUG_H
#define DEBUG_H

#define DDR_DEBUG 1
#if DDR_DEBUG
extern int print(const char *fmt, ...);
#define	INFO(...)	print(__VA_ARGS__)
// #define	INFO(...)
#define	LOG(...)	print(__VA_ARGS__)
#define	ERROR(...)	print(__VA_ARGS__)
#else
#define	INFO(...)
#define	ERROR(...)
#endif
#define	VERBOSE(...)
#define ARRAY_SIZE(X) (sizeof(X)/(sizeof(X[0])))

#define	panic(...)	while(1)
#define	dsb(...)

#endif /* DEBUG_H */

