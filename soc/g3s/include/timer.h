/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef DRIVERS_TIMER_INC_TIMER_H_
#define DRIVERS_TIMER_INC_TIMER_H_

#define TIMEOUT_VALUE  (0)  /* If it's not work with 0, change it to appropriate small value such as 1...5 */
#define OSTM_NOTIMEOUT (0)
#define OSTM_TIMEOUT   (1)

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
extern void ostm_start_timer_1ms(uint32_t x_ms);
extern void ostm_start_timer_1us(uint32_t x_us);
extern void emmc_wait_8cycle_mmc_clk(void);
extern void emmc_wait_74cycle_mmc_clk( void );

extern void ostm_stop_timer(void);
extern uint32_t ostm_get_counter(void);
extern int32_t ostm_is_timeout(void);
extern void ostm_wait_timer_ms(uint32_t x_ms);
extern void ostm_wait_timer_us(uint32_t x_us);

#endif /* DRIVERS_TIMER_INC_TIMER_H_ */

/* End of File */
