/*
 * Copyright (c) 2023, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : timer.c
 * Version      : 1.0
 * Description  : OSTM.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>
#include <rz_soc_def.h>
#include "timer.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define OSTM0CMP_0    ((volatile uint32_t *)( RZG3S_GTM0_BASE + 0x000 ))  /* OSTM compare register_0 */
#define OSTM0CNT_0    ((volatile uint32_t *)( RZG3S_GTM0_BASE + 0x004 ))  /* OSTM counter register_0 */
#define OSTM0TE_0     ((volatile uint8_t *) ( RZG3S_GTM0_BASE + 0x010 ))  /* OSTM count enable status register_0 */
#define OSTM0TS_0     ((volatile uint8_t *) ( RZG3S_GTM0_BASE + 0x014 ))  /* OSTM count start trigger register_0 */
#define OSTM0TT_0     ((volatile uint8_t *) ( RZG3S_GTM0_BASE + 0x018 ))  /* OSTM count stop trigger register_0 */
#define OSTM0CTL_0    ((volatile uint8_t *) ( RZG3S_GTM0_BASE + 0x020 ))  /* OSTM control register_0 */

#define OSTM_1MS_COUNT ( 12500 + 1 )    /* Counter value per 1ms */
#define OSTM_1US_OCUNT ( 12 + 1 )       /* Counter value per 1us */

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ostm_start_timer_1ms
 * Description  : Start OSTM.
 * Arguments    : uint32_t x_ms; I : Wait period[ms].
 * Return Value : none.
 * Note         : OSTM Base Clock is PL2
 *              : PL2:100MHz(max)
 *              : 1 Count = 10.0 [ns]
 *********************************************************************************************************************/
void ostm_start_timer_1ms(uint32_t x_ms)
{

    /* Timer stop */
    *OSTM0TT_0 = 0x01;

    /* OSTM control register setting */
    *OSTM0CTL_0 = 0x00;    /* Interval timer mode(down count),
                           * Disables interrupt at counter operation start */
    /* OSTM compare register setting */
    *OSTM0CMP_0 = (OSTM_1MS_COUNT * x_ms);  /* Calculate counter Value*/

    /* Timer start */
    *OSTM0TS_0 = 0x01;

    /* Make sure the timer is working */
    while (1 != (*OSTM0TE_0))
    {
        /* Continue to Loop until enable */
    }

    /* Set TIMEOUT_VALUE to "OSTM compare register", during timer operation */
    /* Just after the last set count value (33333 * x_ms) reaches 0, TIMEOUT_VALUE is enabled. */
    *OSTM0CMP_0 = TIMEOUT_VALUE;
}
/**********************************************************************************************************************
 * End of function ostm_start_timer_1ms
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ostm_start_timer_1us
 * Description  : Start OSTM.
 * Arguments    : uint32_t x_us; I : Wait Period[us].
 * Return Value : none.
 * Note         : OSTM Base Clock is PL2
 *              : PL2 :100MHz(max)
 *              : 1 Count = 10.0 [ns]
 *********************************************************************************************************************/
void ostm_start_timer_1us(uint32_t x_us)
{
    /* Timer stop */
    *OSTM0TT_0 = 0x01;

    /* OSTM control register setting */
    *OSTM0CTL_0 = 0x00;    /* Interval timer mode(down count),
                           * Disable interrupt at counter operation start */
    /* OSTM compare register setting */
    *OSTM0CMP_0 = (OSTM_1US_OCUNT * x_us);  /* Calculate counter Value*/

    /* Timer start */
    *OSTM0TS_0 = 0x01;

    /* Make sure the timer is working */
    while (1 != (*OSTM0TE_0))
    {
        /* Continue to Loop until enable */
    }
    /* Set TIMEOUT_VALUE to "OSTM compare register", during timer operation */
    *OSTM0CMP_0 = TIMEOUT_VALUE;
}
/**********************************************************************************************************************
 * End of function ostm_start_timer_1us
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: emmc_wait_8cycle_mmc_clk
 * Description  : Wait 8clock.
 * Arguments    : none.
 * Return Value : none.
 * Note         : OSTM Base Clock is P1(phi)
 *              : P1(phi) :66MHz(max)
 *              : 1 Count = 15.1515 [ns]
 *********************************************************************************************************************/
void emmc_wait_8cycle_mmc_clk( void )
{

    ostm_start_timer_1us(32);

    while( ostm_is_timeout() !=  OSTM_TIMEOUT)
    {
        /* No operation */
    }

    ostm_stop_timer();

}
/**********************************************************************************************************************
 * End of function emmc_wait_8cycle_mmc_clk
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: emmc_wait_74cycle_mmc_clk
 * Description  : Wait 74 clock.
 * Arguments    : none.
 * Return Value : none.
 * Note         : OSTM Base Clock is P1(phi)
 *              : P1(phi) :66MHz(max)
 *              : 1 Count = 15.1515 [ns]
 *********************************************************************************************************************/
void emmc_wait_74cycle_mmc_clk( void )
{

    ostm_start_timer_1us(288);
    while( ostm_is_timeout() !=  OSTM_TIMEOUT)
    {
        /* No operation */
    }
    ostm_stop_timer();
}
/**********************************************************************************************************************
 * End of function emmc_wait_74cycle_mmc_clk
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ostm_stop_timer
 * Description  : Stop OSTM and initialize OSTM register.
 * Arguments    : none.
 * Return Value : none.
 * Note         : OSTM0CNT_0, OSTM0TE_0 are read-only
 *              : Because OSTM0TS_0 and OSTM0TT_0 are write-only, cannot be returned to the initial value
 *********************************************************************************************************************/
void ostm_stop_timer(void)
{

    /* OSTM STOP*/
    *OSTM0TT_0 = 0x01;

    while (0 != (*OSTM0TE_0))
    {
        /* Continue to Loop until enable */
    }

    /* OSTM control register initialize */
    *OSTM0CTL_0 = 0x00;

    /* OSTM compare register initialize */
    *OSTM0CMP_0 = 0x00000000;
}
/**********************************************************************************************************************
 * End of function ostm_stop_timer
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ostm_get_counter
 * Description  : Get OSTM Count values.
 * Arguments    : none.
 * Return Value : counter value(uint32_t).
 *********************************************************************************************************************/
uint32_t ostm_get_counter(void)
{
    return (*OSTM0CNT_0);
}
/**********************************************************************************************************************
 * End of function ostm_get_counter
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ostm_is_timeout
 * Description  : Check OSTM timeout.
 * Arguments    : none.
 * Return Value : 1 : Timeout occurs
 *              : 0 : Timer running
 *********************************************************************************************************************/
int32_t ostm_is_timeout(void)
{
    uint32_t counter;
    int32_t  ret;

    counter = ostm_get_counter();

    if(counter <= TIMEOUT_VALUE)
    {
        /* Detect the timeout, when the counter value is less than the threshold */
        ret = OSTM_TIMEOUT;
    }
    else
    {
        ret = OSTM_NOTIMEOUT;
    }
    return ret;
}
/**********************************************************************************************************************
 * End of function ostm_is_timeout
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ostm_wait_timer_ms
 * Description  : Wait OSTM timer.
 * Arguments    : uint32_t x_ms; I : Wait period[ms].
 * Return Value : none.
 * Note         : OSTM Base Clock is PL2
 *              : PL2:100MHz(max)
 *              : 1 Count = 10.0 [ns]
 *********************************************************************************************************************/
void ostm_wait_timer_ms(uint32_t x_ms)
{
    ostm_start_timer_1ms(x_ms);
    while (OSTM_TIMEOUT != ostm_is_timeout())
    {
        /* No operation */
    }
    ostm_stop_timer();
}
/**********************************************************************************************************************
 * End of function ostm_wait_timer_ms
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ostm_wait_timer_us
 * Description  : Wait OSTM timer.
 * Arguments    : uint32_t x_us; I : Wait Period[us].
 * Return Value : none.
 * Note         : OSTM Base Clock is PL2
 *              : PL2 :100MHz(max)
 *              : 1 Count = 10.0 [ns]
 *********************************************************************************************************************/
void ostm_wait_timer_us(uint32_t x_us)
{
    ostm_start_timer_1us(x_us);
    while (OSTM_TIMEOUT != ostm_is_timeout())
    {
        /* No operation */
    }
    ostm_stop_timer();
}
/**********************************************************************************************************************
 * End of function ostm_wait_timer_us
 *********************************************************************************************************************/

/* End of File */
