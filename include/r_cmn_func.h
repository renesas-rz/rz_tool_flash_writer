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
 * Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_cmn_func.h
 * Version      : 00.40
 * Description  : common functions header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#ifndef R_CMN_FUNC_H
#define R_CMN_FUNC_H

#define R_CMN_DMB()                     __asm volatile ("     dmb sy\n")
#define R_CMN_DSB()                     __asm volatile ("     dsb sy\n")

#define R_CMN_WFI()                     __asm volatile ("     WFI\n")
#define R_CMN_NOP()                     __asm volatile ("     nop\n")

#define R_CMN_strtouint32               R_CMN_StringToUint32
#define R_CMN_strtouintptr              R_CMN_StringToUintptr
#define R_CMN_strtoint32                R_CMN_StringToInt32
#define CMN_DelayInUS(m_us)             R_CMN_DelayInUS((m_us))
#define CMN_DelayInMS(m_ms)             R_CMN_DelayInUS((m_ms) * 1000)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/
typedef enum
{
    CMN_NO_ERROR = 0,

    /* below add error code */
    CMN_ERR_PARAMETER                   = -1025,
    CMN_ERR_UNSUPPORTED                 = -1026,
    CMN_ERR_TIMEOUT                     = -1027,
    CMN_ERR_NOT_OPEN                    = -1028,
    CMN_ERR_BUSY                        = -1029,
    CMN_ERR_OVERFLOW                    = -1030,
    CMN_ERR_UNDERFLOW                   = -1031,
    CMN_ERR_ABORTED                     = -1032,
    CMN_ERR_PARITY                      = -1033,
    CMN_ERR_STATE                       = -1034,
    CMN_ERR_NOT_FOUND                   = -1035,
    CMN_ERR_NOT_EXIST                   = -1036,
    CMN_ERR_NO_SPACE                    = -1037,

    RTC_NO_ERROR                        = 0,
    RTC_NO_ERROR_INIT_SKIP              = -2049,
    RTC_ERR_PARAM                       = -2050,
    RTC_ERR_UNINIT                      = -2051,
    RTC_ERR_STOP                        = -2052,
    RTC_ERR_BUSY                        = -2053,
    RTC_ERR_TIMEOUT                     = -2054,
    RTC_ERR_INTC                        = -2055,

    USBH_NO_ERROR                       = 0,
    USBH_ERR_PARAM                      = -3073,
    USBH_ERR_STATE                      = -3074,
    USBH_ERR_OVER_LEN                   = -3075,
    USBH_ERR_REQ_FULL                   = -3076,
    USBH_ERR_NOT_SUPPORTED              = -3077,
    USBH_ERR_NO_SPACE                   = -3078,
    USBH_ERR_TRANSFER_FAILED            = -3079,

} cmn_err_t;

typedef int32_t (PutsFunc_t)(uint8_t *, uint32_t);

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
static inline uint8_t   R_CMN_REG_READ8(uintptr_t addr)
{
    return *((volatile uint8_t *)addr);
}

static inline uint16_t  R_CMN_REG_READ16(uintptr_t addr)
{
    return *((volatile uint16_t *)addr);
}

static inline uint32_t  R_CMN_REG_READ32(uintptr_t addr)
{
    return *((volatile uint32_t *)addr);
}

static inline uint64_t  R_CMN_REG_READ64(uintptr_t addr)
{
    return *((volatile uint64_t *)addr);
}

static inline void      R_CMN_REG_WRITE8(uintptr_t addr, uint8_t value)
{
    *((volatile uint8_t *)addr) = value;
}

static inline void      R_CMN_REG_WRITE16(uintptr_t addr, uint16_t value)
{
    *((volatile uint16_t *)addr) = value;
}

static inline void      R_CMN_REG_WRITE32(uintptr_t addr, uint32_t value)
{
    *((volatile uint32_t *)addr) = value;
}

static inline void      R_CMN_REG_WRITE64(uintptr_t addr, uint64_t value)
{
    *((volatile uint64_t *)addr) = value;
}

extern void     R_CMN_InitSysCnt (void);
extern uint64_t R_CMN_GetSysCnt (void);
extern uint64_t R_CMN_GetFreq4SysCnt (void);

extern void   * R_CMN_memset (void *p_dst, uint8_t ch, uint32_t size);
extern void   * R_CMN_memcpy (void *p_dst, void *p_src, uint32_t size);
extern int32_t  R_CMN_strcmp (const uint8_t *p_str1, const uint8_t *p_str2);
extern int32_t  R_CMN_strlen (const uint8_t *p_str);
extern int32_t  R_CMN_StringToUint32 (uint8_t *p_str, uint32_t *p_dat, uint32_t radix);
extern int32_t  R_CMN_StringToUintptr (uint8_t *p_str, uintptr_t *p_dat, uint32_t radix);
extern int32_t  R_CMN_StringToInt32 (uint8_t *p_str, int32_t *p_dat, uint32_t radix);
extern int32_t  R_CMN_get_index (const uint8_t *p_str, const uint8_t *p_tbl[], uint32_t num);
extern int32_t  R_CMN_get_character (uint8_t *p_ch);
extern int32_t  R_CMN_printf (const uint8_t *p_fmt, ...);

extern void     R_CMN_Initialize (void);
extern void     R_CMN_DelayInUS (int32_t usec);

extern int32_t  R_CMN_SetPutsFunc (uint32_t id, PutsFunc_t *pf);
extern int32_t  R_CMN_SetPutsFunc4Serial (void);
extern int32_t  R_CMN_SetPutsFunc4UARTPIO (void);

#endif  /* !defined(R_CMD_ANA_H) */
