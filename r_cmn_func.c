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
 * File Name    : r_cmn_func.c
 * Version      : 00.42
 * Description  : common functions.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

//#include "rzg3l_base_addr.h"
#include "r_cmn_func.h"
//#include "uart.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define SYSCNT_BASE_ADDRESS             (BASE_ADDRESS_SYC)
#define SYSCNT_CNTCR_OFFSET             (0x0000)
#define SYSCNT_CNTCVL_OFFSET            (0x0008)
#define SYSCNT_CNTFID0_OFFSET           (0x0020)

#define SYSCNT_FREQUENCY                (24000000)

#define SYSCNT_CNTCR_EN                 (0x01 << 0)
#define SYSCNT_CNTCR_HDBG				(0x01 << 1)

#define CMN_PRINT_OUT_ID_NUM            (2)

#define R_CMN_NUMBER_TO_STR(m_wk, m_width, m_sz, m_flag, m_ap, m_uqtmp, m_ultmp, m_pch)     \
{                                                                                           \
    int32_t rslt;                                                                           \
    if (sizeof((m_wk)) <= (m_width))                                                        \
    {                                                                                       \
        (m_width) = sizeof((m_wk)) - 1;                                                     \
    }                                                                                       \
    if (8 == (m_sz))                                                                        \
    {                                                                                       \
        (m_uqtmp) = va_arg((m_ap), uint64_t);                                               \
        rslt = r_cmn_uint64_to_str((m_wk), sizeof((m_wk)), (m_uqtmp), (m_width), (m_flag));   \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        (m_ultmp) = va_arg((m_ap), uint32_t);                                               \
        rslt = r_cmn_uint32_to_str((m_wk), sizeof((m_wk)), (m_ultmp), (m_width), (m_flag));   \
    }                                                                                       \
    (m_pch) = (m_wk);                                                                       \
    if (0 > rslt)                                                                           \
    {                                                                                       \
        (m_wk)[0] = '\0';                                                                   \
    }                                                                                       \
}

#define R_CMN_PUTS(m_id, m_buff, m_cnt, m_limit)            \
{                                                           \
    if ((m_cnt) >= (m_limit))                               \
    {                                                       \
        r_cmn_put_string((m_id), (m_buff), (m_cnt));        \
        (m_cnt) = 0;                                        \
    }                                                       \
}

#define R_CMN_PUT_CHAR(m_buff, m_cnt, m_ch) \
{                                           \
    if (0 < (m_cnt))                        \
    {                                       \
        *(m_buff) = (m_ch);                 \
        (m_buff)++;                         \
        (m_cnt)--;                          \
        if (1 == (m_cnt))                   \
        {                                   \
            *(m_buff) = '\0';               \
            (m_cnt)--;                      \
        }                                   \
    }                                       \
}

#define ARRAY_NUM(m_array)  (sizeof((m_array))/sizeof((m_array)[0]))

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
typedef struct
{
    int32_t (*pf_puts)(uint8_t *, uint32_t);
} st_printf_out_info;

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
static int32_t  r_cmn_uint32_to_str (uint8_t *p_buff, uint32_t size, uint32_t dat, uint32_t width, uint32_t flag);
static int32_t  r_cmn_int32_to_str (uint8_t *p_buff, uint32_t size, int32_t dat, uint32_t width, uint32_t flag);
static int32_t  r_cmn_uint64_to_str (uint8_t *p_buff, uint32_t size, uint64_t dat, uint32_t width, uint32_t flag);
static int32_t  r_cmn_int64_to_str (uint8_t *p_buff, uint32_t size, int64_t dat, uint32_t width, uint32_t flag);
static int32_t  r_cmn_put_string (uint32_t id, uint8_t *p_buff, uint32_t size);
static int32_t  r_cmn_puts_serial (uint8_t *p_buff, uint32_t size);
static int32_t  r_cmn_puts_uart_pio (uint8_t *p_buff, uint32_t size);

extern int32_t  r_cmn_vprintf_id (uint32_t id, const uint8_t *p_fmt, va_list ap);

static st_printf_out_info gl_printf_out_info[CMN_PRINT_OUT_ID_NUM];

/*
 * define flag values for convert int to str
 */
static const uint32_t flag_zero_padding  = 0x00000001;
static const uint32_t flag_blank_padding = 0x00000010;
static const uint32_t flag_signal        = 0x00000100;
static const uint32_t flag_signal_minus  = 0x00000200;
static const uint32_t flag_upper         = 0x00001000;
static const uint32_t flag_hex           = 0x00002000;
static const uint32_t flag_hex_add_head  = 0x00004000;
static const uint32_t flag_dec           = 0x00010000;

/**********************************************************************************************************************
 * Function Name: R_CMN_Initialize
 * Description  : common function initialize
 * Arguments    : void
 *              : 
 * Return Value : void
 *********************************************************************************************************************/
void R_CMN_Initialize(void)
{
    R_CMN_InitSysCnt();

    {
        gl_printf_out_info[0].pf_puts = r_cmn_puts_serial;
        gl_printf_out_info[1].pf_puts = r_cmn_puts_uart_pio;

        uart_init(0);
    }
}
/**********************************************************************************************************************
 End of function R_CMN_Initialize
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Function Name: r_cmn_SYC_ReadReg
 * Description  : read access to System Counter register
 * Arguments    : uint32_t offset		: SYC register offset
 * Return Value : uint32_t				: read data
 *********************************************************************************************************************/
static inline uint32_t r_cmn_SYC_ReadReg(uint32_t offset)
{
	return (R_CMN_REG_READ32(SYSCNT_BASE_ADDRESS + offset));
}
/*********************************************************************************************************************
 End of function r_cmn_SYC_ReadReg
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Function Name: r_cmn_SYC_WriteReg
 * Description  : read access to System Counter register
 * Arguments    : uint32_t offset		: SYC register offset
 *              : uint32_t value		: write data
 * Return Value : none
 *********************************************************************************************************************/
static inline void r_cmn_SYC_WriteReg(uint32_t offset, uint32_t value)
{
	R_CMN_REG_WRITE32((SYSCNT_BASE_ADDRESS + offset), value);
}
/**********************************************************************************************************************
 End of function r_cmn_SYC_WriteReg
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_InitSysCnt
 * Description  : initialize system counter
 * Arguments    : none
 * Return Value : none
 *********************************************************************************************************************/
void R_CMN_InitSysCnt(void)
{
    r_cmn_SYC_WriteReg(SYSCNT_CNTFID0_OFFSET, SYSCNT_FREQUENCY);
    r_cmn_SYC_WriteReg(SYSCNT_CNTCR_OFFSET, SYSCNT_CNTCR_EN | SYSCNT_CNTCR_HDBG);
}
/**********************************************************************************************************************
 End of function R_CMN_InitSysCnt
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_GetSysCnt
 * Description  : get system counter
 * Arguments    : none
 * Return Value : system counter
 *********************************************************************************************************************/
uint64_t R_CMN_GetSysCnt(void)
{
    return R_CMN_REG_READ64(SYSCNT_BASE_ADDRESS + SYSCNT_CNTCVL_OFFSET);
}
/**********************************************************************************************************************
 End of function R_CMN_GetSysCnt
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_GetFreq4SysCnt
 * Description  : get system counter
 * Arguments    : none
 * Return Value : system counter
 *********************************************************************************************************************/
uint64_t R_CMN_GetFreq4SysCnt(void)
{
    return (uint64_t)R_CMN_REG_READ32(SYSCNT_BASE_ADDRESS + SYSCNT_CNTFID0_OFFSET);
}
/**********************************************************************************************************************
 End of function R_CMN_GetFreq4SysCnt
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_DelayInUS
 * Description  : delay in us.
 * Arguments    : int32_t usec : wait time.
 *              : 
 * Return Value : void
 *                
 *********************************************************************************************************************/
void R_CMN_DelayInUS(int32_t usec)
{
    uint64_t    start   = R_CMN_GetSysCnt();
    uint64_t    cycles  = (R_CMN_GetFreq4SysCnt() / 1000000UL) * usec;

    while ((R_CMN_GetSysCnt() - start) < cycles)
    {
        R_CMN_NOP();
    }
}
/**********************************************************************************************************************
 End of function R_CMN_DelayInUS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_memset
 * Description  : memory area data set.
 * Arguments    : void *p_dst   : top address for memory area.
 *              : uint8_t ch    : target data.
 *              : uint32_t size : target memory area size [byte].
 *              : 
 * Return Value : top address for memory area.
 *                
 *********************************************************************************************************************/
void *R_CMN_memset(void *p_dst, uint8_t ch, uint32_t size)
{
    void *rslt = p_dst;
    volatile uint8_t *p_u8 = (uint8_t *)p_dst;

    if (NULL == p_dst)
    {}
    else
    while (0 < size)
    {
        /*
         * It is the same pointer type.
         */
        *(p_u8) = ch;
        p_u8 += 1;
        size -= 1;
    }

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_memset
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_memcpy
 * Description  : copy data.
 * Arguments    : void *p_dst   : top address for destination memory area.
 *              : void *p_src   : top address for source memory area.
 *              : uint32_t size : copy size [byte].
 *              : 
 * Return Value : top address for destination memory area.
 *                
 *********************************************************************************************************************/
void *R_CMN_memcpy(void *p_dst, void *p_src, uint32_t size)
{
    void *rslt = p_dst;
    /*
     * It is the same pointer type.
     */
    uint8_t *p_src_u8 = (uint8_t *)p_src;
    uint8_t *p_dst_u8 = (uint8_t *)p_dst;

    if ((NULL == p_dst) || (NULL == p_src))
    {}
    else
    while (0 < size)
    {
        *(p_dst_u8) = *(p_src_u8);
        size--;
        p_dst_u8 += 1;
        p_src_u8 += 1;
    }

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_memcpy
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_strcmp
 * Description  : compare strings.
 * Arguments    : const uint8_t *p_str1 : top address for target string (1).
 *              : const uint8_t *p_str2 : top address for target string (2).
 *              : 
 * Return Value : result compared.
 *                 1 : (1) > (2)
 *                 0 : (1) == (2)
 *                -1 : (1) < (2)
 *********************************************************************************************************************/
int32_t R_CMN_strcmp(const uint8_t *p_str1, const uint8_t *p_str2)
{
    int32_t rslt = 0;

    do
    {
        if (NULL == p_str1 || NULL == p_str2)
        {
            if (NULL == p_str1 && NULL == p_str2)
            {
                rslt = 0;
            }
            else if (NULL == p_str2)
            {
                rslt = 1;
            }
            else /* if (NULL == p_str1) */
            {
                rslt = -1;
            }
            break;
        }

        while (('\0' != *p_str1) && ('\0' != *p_str2))
        {
            if (*p_str1 != *p_str2)
            {
                break;
            }
            p_str1++;
            p_str2++;
        }

        if (('\0' == *p_str1) && ('\0' != *p_str2))
        {
            rslt = -1;
        }
        else if (('\0' != *p_str1) && ('\0' == *p_str2))
        {
            rslt = 1;
        }
        else if (('\0' == *p_str1) && ('\0' == *p_str2))
        {
            rslt = 0;
        }
        else /** if ('\0' != *p_str1 && '\0' != *p_str2) */
        {
            if (*p_str1 < *p_str2)
            {
                rslt = -1;
            }
            if (*p_str1 > *p_str2)
            {
                rslt = 1;
            }
        }
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_strcmp
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_strlen
 * Description  : count characters in string.
 * Arguments    : const uint8_t *p_str1 : top address for target string.
 *              : 
 * Return Value : result count number.
 *                0 <= character counts.
 *********************************************************************************************************************/
int32_t R_CMN_strlen(const uint8_t *p_str)
{
    int32_t cnt = 0;

    do
    {
        if (NULL == p_str)
        {
            break;
        }

        while ('\0' != *p_str)
        {
            p_str++;
            cnt++;
        }
    }
    while (0);

    return (cnt);
}
/**********************************************************************************************************************
 End of function R_CMN_strlen
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_get_index
 * Description  : search element number (for string)
 * Arguments    : const uint8_t *p_str   : top address for target string.
 *              : const uint8_t *p_tbl[] : top address for table.
 *              : uint32_t num           : number of table elements.
 *              : 
 * Return Value : element index number.
 *                0 <=  : index number.
 *                CMN_ERR_NOT_FOUND : not find.
 *********************************************************************************************************************/
int32_t R_CMN_get_index(const uint8_t *p_str, const uint8_t *p_tbl[], uint32_t num)
{
    int32_t rslt = CMN_ERR_NOT_FOUND;
    int32_t ch = 0;

    while (ch < num)
    {
        if (!R_CMN_strcmp(p_str, p_tbl[ch]))
        {
            rslt = ch;
            break;
        }
        ch++;
    }

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_get_index
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_StringToUint32
 * Description  : convert string to uint32_t value.
 * Arguments    : uint8_t *p_str  : top address for target string.
 *              : uint32_t *p_dat : top address for convert value save area.
 *              : uint32_t radix  : convert radix (0 is judge in string)
 *              : 
 * Return Value : convert character number.
 *                0 <=  : convert character number.
 *                CMN_ERR_PARAMETER : parameter error.
 *********************************************************************************************************************/
int32_t R_CMN_StringToUint32(uint8_t *p_str, uint32_t *p_dat, uint32_t radix)
{
    int32_t  rslt = CMN_ERR_NOT_FOUND;
    uint32_t udat = 0;
    int32_t  signal = 1;
    uint32_t cnv = 0;
    uint32_t cnt = 0;

    do
    {
        if (NULL == p_str || NULL == p_dat)
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        if (0 == radix)
        {
            if (('0' == p_str[0]) && (('x' == p_str[1]) || ('X' == p_str[1])) )
            {
                radix = 16;
                p_str += 2;
            }
            else if (('0' == p_str[0]) && (('0' <= p_str[1]) && (p_str[1] <= '7')) )
            {
                radix = 8;
                p_str++;
            }
            else
            {
                radix = 10;
            }
        }

        if (16 == radix)
        {
            if (('0' == p_str[0]) && (('x' == p_str[1]) || ('X' == p_str[1])) )
            {
                p_str += 2;
            }
        }

        if (10 == radix)
        {
            while (('-' == p_str[0]) || ('+' == p_str[0]))
            {
                if ('-' == p_str[0])
                {
                    signal = -1;
                    p_str++;
                }

                if ('+' == p_str[0])
                {
                    signal = 1;
                    p_str++;
                }
            }
        }

        while ('\0' != p_str[0])
        {
            if (('0' <= p_str[0]) && (p_str[0] <= '9'))
            {
                cnv = p_str[0] - '0';
            }
            else if (('a' <= p_str[0]) && (p_str[0] <= 'f'))
            {
                cnv = p_str[0] - 'a' + 0x0a;
            }
            else if (('A' <= p_str[0]) && (p_str[0] <= 'F'))
            {
                cnv = p_str[0] - 'A' + 0x0a;
            }
            else
            {
                break;
            }

            if (cnv >= radix)
            {
                break;
            }

            udat *= radix;
            udat += cnv;
            p_str++;
            cnt++;
        }

        if (10 == radix)
        {
            /*
             * This data is abs(original data).
             * abs(original data) is in int32_t range.
             */
            udat = (uint32_t)((int32_t)udat * signal);
        }

        if (0 == cnt)
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        *p_dat = udat;

        /*
         * convert count is in int32_t range.
         */
        rslt = (int32_t)cnt;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_StringToUint32
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_StringToUintptr
 * Description  : convert string to uint32_t value.
 * Arguments    : uint8_t *p_str  : top address for target string.
 *              : uint32_t *p_dat : top address for convert value save area.
 *              : uint32_t radix  : convert radix (0 is judge in string)
 *              : 
 * Return Value : convert character number.
 *                0 <=  : convert character number.
 *                CMN_ERR_PARAMETER : parameter error.
 *********************************************************************************************************************/
int32_t R_CMN_StringToUintptr(uint8_t *p_str, uintptr_t *p_dat, uint32_t radix)
{
    int32_t   rslt = CMN_ERR_NOT_FOUND;
    uintptr_t udat = 0;
    int32_t   signal = 1;
    uint32_t  cnv = 0;
    uint32_t  cnt = 0;

    do
    {
        if ((NULL == p_str) || (NULL == p_dat))
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        if (0 == radix)
        {
            if ( ('0' == p_str[0]) && (('x' == p_str[1]) || ('X' == p_str[1])) )
            {
                radix = 16;
                p_str += 2;
            }
            else if ( ('0' == p_str[0]) && (('0' <= p_str[1]) && (p_str[1] <= '7')) )
            {
                radix = 8;
                p_str++;
            }
            else
            {
                radix = 10;
            }
        }

        if (16 == radix)
        {
            if ( ('0' == p_str[0]) && (('x' == p_str[1]) || ('X' == p_str[1])) )
            {
                p_str += 2;
            }
        }

        if (10 == radix)
        {
            while (('-' == p_str[0]) || ('+' == p_str[0]))
            {
                if ('-' == p_str[0])
                {
                    signal = -1;
                    p_str++;
                }

                if ('+' == p_str[0])
                {
                    signal = 1;
                    p_str++;
                }
            }
        }

        while ('\0' != p_str[0])
        {
            if (('0' <= p_str[0]) && (p_str[0] <= '9'))
            {
                cnv = p_str[0] - '0';
            }
            else if (('a' <= p_str[0]) && (p_str[0] <= 'f'))
            {
                cnv = p_str[0] - 'a' + 0x0a;
            }
            else if (('A' <= p_str[0]) && (p_str[0] <= 'F'))
            {
                cnv = p_str[0] - 'A' + 0x0a;
            }
            else
            {
                break;
            }

            if (cnv >= radix)
            {
                break;
            }

            udat *= radix;
            udat += cnv;
            p_str++;
            cnt++;
        }

        if (10 == radix)
        {
            /*
             * This data is abs(original data).
             * abs(original data) is in intptr_t range.
             */
            udat = (uintptr_t)((intptr_t)udat * signal);
        }

        if (0 == cnt)
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        *p_dat = udat;
        /*
         * convert count is in int32_t range.
         */
        rslt = (int32_t)cnt;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_StringToUintptr
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_StringToInt32
 * Description  : convert string to uint32_t value.
 * Arguments    : uint8_t *p_str  : top address for target string.
 *              : uint32_t *p_dat : top address for convert value save area.
 *              : uint32_t radix  : convert radix (0 is judge in string)
 *              : 
 * Return Value : convert character number.
 *                0 <=  : convert character number.
 *                CMN_ERR_PARAMETER : parameter error.
 *********************************************************************************************************************/
int32_t R_CMN_StringToInt32(uint8_t *p_str, int32_t *p_dat, uint32_t radix)
{
    int32_t  rslt = CMN_ERR_NOT_FOUND;
    int32_t  dat = 0;
    int32_t  signal = 1;
    uint32_t cnv = 0;
    uint32_t cnt = 0;

    do
    {
        if (NULL == p_str || NULL == p_dat)
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        if (0 == radix)
        {
            if (('0' == p_str[0]) && (('x' == p_str[1]) || ('X' == p_str[1])) )
            {
                radix = 16;
                p_str += 2;
            }
            else if (('0' == p_str[0]) && (('0' <= p_str[1]) && (p_str[1] <= '7')) )
            {
                radix = 8;
                p_str++;
            }
            else
            {
                radix = 10;
            }
        }

        if (16 == radix)
        {
            if (('0' == p_str[0]) && (('x' == p_str[1]) || ('X' == p_str[1])) )
            {
                p_str += 2;
            }
        }

        if (10 == radix)
        {
            while (('-' == p_str[0]) || ('+' == p_str[0]))
            {
                if ('-' == p_str[0])
                {
                    signal = -1;
                    p_str++;
                }

                if ('+' == p_str[0])
                {
                    signal = 1;
                    p_str++;
                }
            }
        }

        while ('\0' != p_str[0])
        {
            if (('0' <= p_str[0]) && (p_str[0] <= '9'))
            {
                cnv = p_str[0] - '0';
            }
            else if (('a' <= p_str[0]) && (p_str[0] <= 'f'))
            {
                cnv = p_str[0] - 'a' + 0x0a;
            }
            else if (('A' <= p_str[0]) && (p_str[0] <= 'F'))
            {
                cnv = p_str[0] - 'A' + 0x0a;
            }
            else
            {
                break;
            }

            if (cnv >= radix)
            {
                break;
            }

            dat *= radix;
            dat += cnv;
            p_str++;
            cnt++;
        }

        if (10 == radix)
        {
            dat = dat * signal;
        }

        if (0 == cnt)
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        *p_dat = dat;

        /*
         * convert count is in int32_t range.
         */
        rslt = (int32_t)cnt;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_StringToInt32
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_CMN_get_character
 * Description  : get character.
 * Arguments    : uint8_t *p_fmt  : top address for target string.
 *              : ...             : parameter data in format indicate.
 *              : 
 * Return Value : Error code. or count for character.
 *                
 *********************************************************************************************************************/
int32_t R_CMN_get_character(uint8_t *p_ch)
{
    int32_t rslt = CMN_ERR_UNSUPPORTED;

    /*
     * it is the same pointer type.
     */
    rslt = UART_PIO_getc(p_ch);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_get_character
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_printf
 * Description  : print string for format.
 * Arguments    : uint8_t *p_fmt  : top address for target string.
 *              : ...             : parameter data in format indicate.
 *              : 
 * Return Value : Error code.
 *                CMN_NO_ERROR : safety end.
 *********************************************************************************************************************/
int32_t R_CMN_printf(const uint8_t *p_fmt, ...)
{
    int32_t     rslt    = CMN_ERR_NOT_FOUND;
    va_list     ap      = { 0 };

    va_start(ap, p_fmt);

    rslt = r_cmn_vprintf_id(0, p_fmt, ap);

    va_end(ap);

    return rslt;
}
/**********************************************************************************************************************
 End of function R_CMN_printf
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_vprintf_id
 * Description  : print string for format.
 * Arguments    : uint32_t id       : output port number (0=common, 1=warning) 
 *              : uint8_t *p_fmt    : top address for target string.
 *              : va_list ap        : parameter data in format indicate.
 *
 * Return Value : Error code.
 *                CMN_NO_ERROR : safety end.
 *********************************************************************************************************************/
int32_t r_cmn_vprintf_id(uint32_t id, const uint8_t *p_fmt, va_list ap)
{
    int32_t  rslt = CMN_ERR_NOT_FOUND;
    uint64_t uq_dat = 0;
    int64_t  q_dat = 0;
    uint32_t cnt = 0;
    uint32_t idx = 0;
    uint32_t ul_dat = 0;
    int32_t  l_dat = 0;
    uint32_t width = 0;
    int32_t  sz = 0;
    uint32_t flag = 0;
    uint8_t  work[16] = {0};
    uint8_t  fmt_wk[32] = {0};
    uint8_t *p_ch = NULL;
    uint8_t  ch = 0;

    // va_start(ap, p_fmt);

    cnt = 0;
    for (ch = *p_fmt; '\0' != ch; ch = *p_fmt)
    {
        /*
          %[flag][width][.enable size][size]<type>
          <type> = c (character), d(signed integer)
                   u (unsigned integer)
               x (unsigned hex)
               X (unsigned hex upper)
               s (string)
               p (address)
          [flag] = (- : right arrange.)
                   + : signal print.
                   0 : 0 padding with [width]
              ' ': blank
         [width] = integer .
         [size]  = ll/LL with d,u,x,X 64bit.
         */
        if ('%' == ch)
        {
            p_fmt++;
            idx = 0;
            flag = 0;
            sz = 0;

            ch = *p_fmt++;
            if ('+' == ch)
            {
                flag |= flag_signal;
                ch = *p_fmt++;
            }
            if ('0' == ch)
            {
                flag |= flag_zero_padding;
                ch = *p_fmt++;
            }
            if (' ' == ch)
            {
                flag |= flag_blank_padding;
                ch = *p_fmt++;
            }

            while (('0' <= ch) && (ch <= '9'))
            {
                fmt_wk[idx++] = ch;
                ch = *p_fmt++;
            }
            /* width ... */
            if (0 < idx)
            {
                fmt_wk[idx] = '\0';
                rslt = R_CMN_StringToUint32(fmt_wk, &width, 10);
                if (CMN_NO_ERROR > rslt)
                {
                    break;
                }

                if (0 == (flag & flag_zero_padding))
                {
                    flag |= flag_blank_padding;
                }
            }
            if (('l' == ch) || ('L' == ch))
            {
                ch = *p_fmt++;
                if (('l' == ch) || ('L' == ch))
                {
                    sz = 8;
                    ch = *p_fmt++;
                }
            }
            switch (ch)
            {
                case '\0':
                {
                    p_fmt--;
                    fmt_wk[0] = '\0';
                    p_ch = fmt_wk;
                    break;
                }
                case '%':
                {
                    fmt_wk[0] = '%';
                    fmt_wk[1] = '\0';
                    p_ch = fmt_wk;
                    break;
                }
                case 'c':
                {
                    ul_dat = va_arg(ap, int);
                    fmt_wk[0] = ul_dat & 0x0FFU;
                    fmt_wk[1] = '\0';
                    p_ch = fmt_wk;
                    break;
                }
                case 's':
                    /* FALL THROUGH */
                case 'S':
                {
                    p_ch = va_arg(ap, uint8_t * );
                    /* copy string */
                    break;
                }
                case 'd':
                    /* FALL THROUGH */
                case 'D':
                {
                    flag |= flag_dec;
                    if (sizeof(fmt_wk) <= width)
                    {
                        width = sizeof(fmt_wk)-1;
                    }
                    if (8 == sz)
                    {
                        q_dat = va_arg(ap, int64_t);
                        rslt = r_cmn_int64_to_str( fmt_wk, sizeof(fmt_wk), q_dat, width, flag);
                    }
                    else
                    {
                        l_dat = va_arg(ap, int32_t);
                        rslt = r_cmn_int32_to_str( fmt_wk, sizeof(fmt_wk), l_dat, width, flag);
                    }
                    /* int -> str */
                    p_ch = fmt_wk;
                    if (0 > rslt)
                    {
                        fmt_wk[0] = '\0';
                    }
                    break;
                }
                case 'P':
                {
                    flag |= flag_upper;
                    /* FALL THROUGH */
                }
                case 'p':
                {
                    flag |= (flag_hex | flag_hex_add_head);
                    sz = sizeof(uintptr_t);
                    R_CMN_NUMBER_TO_STR(fmt_wk, width, sz, flag, ap, uq_dat, ul_dat, p_ch);
                    break;
                }
                case 'X':
                {
                    flag |= flag_upper;
                    /* FALL THROUGH */
                }
                case 'x':
                {
                    flag |= flag_hex;
                    R_CMN_NUMBER_TO_STR(fmt_wk, width, sz, flag, ap, uq_dat, ul_dat, p_ch);
                    break;
                }
                case 'u':
                    /* FALL THROUGH */
                case 'U':
                {
                    flag |= flag_dec;
                    R_CMN_NUMBER_TO_STR(fmt_wk, width, sz, flag, ap, uq_dat, ul_dat, p_ch);
                    break;
                }
                default:
                {
                    fmt_wk[0] = '\0';
                    p_ch = fmt_wk;
                    break;
                }
            }

            for (ch = *p_ch; '\0' != ch; ch = *p_ch)
            {
                R_CMN_PUTS(id, work, cnt, sizeof(work)-1);
                if ('\n' == ch)
                {
                    work[cnt++] = '\r';
                    work[cnt++] = '\n';
                }
                else
                {
                    work[cnt++] = ch;
                }
                p_ch++;
            }
        }
        else if ('\n' == ch)
        {
            p_fmt++;

            fmt_wk[0] = '\r';
            fmt_wk[1] = '\n';
            fmt_wk[2] = '\0';
            p_ch = fmt_wk;

            R_CMN_PUTS(id, work, cnt, sizeof(work)-1);
            for (ch = *p_ch; '\0' != ch; ch = *p_ch)
            {
                work[cnt++] = ch;
                p_ch++;
            }
        }
        else
        {
            work[cnt++] = ch;
            p_fmt++;
        }

        R_CMN_PUTS(id, work, cnt, sizeof(work));
    }

    R_CMN_PUTS(id, work, cnt, 1);

    // va_end(ap);

    return (CMN_NO_ERROR);
}
/**********************************************************************************************************************
 End of function r_cmn_vprintf_id
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_int_to_str_get_head_size
 * Description  : calculate header character number.
 * Arguments    : uint32_t flag : convert information flags.
 *              : 
 * Return Value : header character number.
 *                0 <= :
 *********************************************************************************************************************/
static int32_t r_cmn_int_to_str_get_head_size(uint32_t flag)
{
    int32_t size = 0;

    if (0 != (flag & flag_dec))
    {
        if (0 != (flag & (flag_signal | flag_signal_minus)))
        {
            size = 1;
        }
    }
    else if (0 != (flag & flag_hex))
    {
        if (0 != (flag & flag_hex_add_head))
        {
            size = 2;
        }
    }

    return (size);
}
/**********************************************************************************************************************
 End of function r_cmn_int_to_str_get_head_size
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_int_to_str_padding_size
 * Description  : calculate padding character number.
 * Arguments    : uint32_t size   : buffer size.
 *              : uint32_t width  : indicate width in format.
 *              : uint32_t digits : digit number for target value.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : padding character number.
 *                0 <= :
 *********************************************************************************************************************/
static int32_t r_cmn_int_to_str_padding_size(uint32_t size, uint32_t width, uint32_t digits, uint32_t flag)
{
    int32_t rslt = CMN_ERR_NOT_FOUND;
    int32_t header_size = 0;

    if ((0 == size) || (0 == width))
    {
        rslt = 0;
    }
    else
    {
        header_size = r_cmn_int_to_str_get_head_size(flag);
        if ((width + header_size + 1) > size)
        {
            width = size - (header_size + 1);
        }

        if (width <= digits)
        {
            width = 0;
        }
        else
        {
            width -= digits;
        }

        rslt = width;
    }

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_int_to_str_padding_size
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_int_to_str_put_head
 * Description  : put character(s) for header(signal).
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : put character number.
 *                0 <= :
 *********************************************************************************************************************/
static int32_t r_cmn_int_to_str_put_head(uint8_t *p_buff, uint32_t size, uint32_t flag)
{
    int32_t rslt = CMN_ERR_NOT_FOUND;

    do
    {
        rslt = 0;
        if (0 != (flag & flag_dec))
        {
            if (0 != (flag & flag_signal))
            {
                if (0 != (flag & flag_signal_minus))
                {
                    p_buff[0] = '-';
                }
                else
                {
                    p_buff[0] = '+';
                }
                rslt = 1;
            }
            else if (0 != (flag & flag_signal_minus))
            {
                p_buff[0] = '-';
                rslt = 1;
            }
        }
        else if ((0 != (flag & flag_hex)) && (0 != (flag & flag_hex_add_head)))
        {
            p_buff[0] = '0';
            p_buff[1] = 'x';
            rslt = 2;
        }
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_int_to_str_padding_size
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_int_to_str_put_padding_and_header
 * Description  : put character(s) for header(signal).
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : uint32_t width  : padding character number.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : put character number.
 *                0 <= :
 *********************************************************************************************************************/
static int32_t r_cmn_int_to_str_put_padding_and_header(uint8_t *p_buff, uint32_t size, uint32_t width, uint32_t flag)
{
    int32_t count = 0;
    int32_t rslt = CMN_ERR_NOT_FOUND;
    int32_t i = 0;

    do
    {
        if (0 != (flag & flag_zero_padding))
        {
            count = 0;
            rslt = r_cmn_int_to_str_put_head(p_buff, size, flag);
            if (0 > rslt)
            {
                break;
            }
            else
            {
                p_buff += rslt;
                count += rslt;
            }

            for (i=0; i < width; i++)
            {
                *p_buff = '0';
                p_buff++;
                count++;
            }
        }
        else if ((0 != (flag & flag_blank_padding)))
        {
            count = 0;
            for (i=0; i < width; i++)
            {
                *p_buff = ' ';
                p_buff++;
                count++;
            }

            rslt = r_cmn_int_to_str_put_head(p_buff, size, flag);
            if (0 > rslt)
            {
                break;
            }
            else
            {
                p_buff += rslt;
                count += rslt;
            }
        }
        else
        {
            count = 0;
            rslt = r_cmn_int_to_str_put_head(p_buff, size, flag);
            if (0 > rslt)
            {
                break;
            }
            else
            {
                p_buff += rslt;
                count += rslt;
            }
        }
        rslt = count;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_int_to_str_put_padding_and_header
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_uint32_to_str_cnv
 * Description  : convert uint32_t data to string.
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : uint32_t dat    : convert data.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : put character number.
 *                0 <= :
 *********************************************************************************************************************/
static int32_t r_cmn_uint32_to_str_cnv(uint8_t *p_buff, uint32_t size, uint32_t dat, uint32_t flag)
{
    int32_t  rslt = CMN_ERR_NOT_FOUND;
    uint32_t radius = 0;
    int32_t  cnt = 0;
    uint8_t  str_wk[12] = { 0 };
    uint8_t  a_code = 0;
    uint8_t  ch = 0;

    do
    {
        if (0 != (flag & flag_hex))
        {
            radius = 16;
        }
        else
        {
            radius = 10;
        }

        if (0 != (flag & flag_upper))
        {
            a_code = 'A';
        }
        else
        {
            a_code = 'a';
        }

        cnt = 0;
        do
        {
            /*
             * radius is 10 or 16.
             * (dat % radius) is in 16.
             */
            ch = (uint8_t)(dat % radius);
            dat /= radius;
            if (ch < 10)
            {
                ch += '0';
            }
            else
            {
                ch = ch - 10u + a_code;
            }
            str_wk[cnt] = ch;
            cnt++;
        }
        while (0 < dat);
        rslt = cnt;

        while (0 < cnt)
        {
            *p_buff = str_wk[cnt-1];
            p_buff++;
            cnt--;
        }
        *p_buff = '\0';
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_uint32_to_str_cnv
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_uint64_to_str_cnv
 * Description  : convert uint32_t data to string.
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : uint64_t dat    : convert data.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : put character number.
 *                0 <= :
 *********************************************************************************************************************/
static int32_t r_cmn_uint64_to_str_cnv(uint8_t *p_buff, uint32_t size, uint64_t dat, uint32_t flag)
{
    int32_t  rslt = CMN_ERR_NOT_FOUND;
    uint32_t radius = 0;
    int32_t  cnt = 0;
    uint8_t  str_wk[20] = { 0 };
    uint8_t  a_code = 0;
    uint8_t  ch = 0;

    do
    {
        if (0 != (flag & flag_hex))
        {
            radius = 16;
        }
        else /** if (0 != (flag & flag_dec)) */
        {
            radius = 10;
        }

        if (0 != (flag & flag_upper))
        {
            a_code = 'A';
        }
        else
        {
            a_code = 'a';
        }

        cnt = 0;
        do
        {
            /*
             * radius is 10 or 16.
             * (dat % radius) is in 16.
             */
            ch = (uint8_t)(dat % radius);
            dat /= radius;
            if (ch < 10)
            {
                ch += '0';
            }
            else
            {
                ch = ch - 10u + a_code;
            }
            str_wk[cnt] = ch;
            cnt++;
        }
        while (dat);
        rslt = cnt;

        while (0 < cnt)
        {
            *p_buff = str_wk[cnt-1];
            p_buff++;
            cnt--;
        }
        *p_buff = '\0';
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_uint64_to_str_cnv
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_uint32_to_str
 * Description  : convert uint32_t data to string.
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : uint32_t dat    : convert data.
 *              : uint32_t width  : digits number.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
static int32_t r_cmn_uint32_to_str(uint8_t *p_buff, uint32_t size, uint32_t dat, uint32_t width, uint32_t flag)
{
    int32_t  rslt = CMN_ERR_NOT_FOUND;
    uint32_t cnt = 0;
    uint32_t i = 0;
    uint8_t  str_wk[12] = { 0 };

    do
    {
        if ((NULL == p_buff) || (0 == size))
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        rslt = r_cmn_uint32_to_str_cnv(str_wk, sizeof(str_wk), dat, flag);
        if (0 > rslt)
        {
            break;
        }
        else
        {
            cnt = rslt;
        }

        width = r_cmn_int_to_str_padding_size(size, width, cnt, flag);

        rslt = r_cmn_int_to_str_put_padding_and_header(p_buff, size, width, flag);
        if (0 > rslt)
        {
            break;
        }

        p_buff += rslt;

        for (i=0; cnt > i; i++)
        {
            *p_buff = str_wk[i];
            p_buff++;
        }
        *p_buff = '\0';
        rslt = CMN_NO_ERROR;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_uint32_to_str
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_int32_to_str
 * Description  : convert uint32_t data to string.
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : int32_t dat     : convert data.
 *              : uint32_t width  : digits number.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 >  : error end.
 *********************************************************************************************************************/
static int32_t r_cmn_int32_to_str(uint8_t *p_buff, uint32_t size, int32_t dat, uint32_t width, uint32_t flag)
{
    int32_t rslt = CMN_ERR_NOT_FOUND;

    do
    {
        if ((0 != (flag & flag_dec)) && (dat < 0))
        {
            flag |= flag_signal_minus;
            dat = -dat;
        }

        /*
         * abs(dat) is in int32_t range.
         * uint32_t range is larger than int32_t range.
         */
        rslt = r_cmn_uint32_to_str(p_buff, size, (uint32_t)dat, width, flag);
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_int32_to_str
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_uint64_to_str
 * Description  : convert uint32_t data to string.
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : uint64_t dat    : convert data.
 *              : uint32_t width  : digits number.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
static int32_t r_cmn_uint64_to_str(uint8_t *p_buff, uint32_t size, uint64_t dat, uint32_t width, uint32_t flag)
{
    int32_t  rslt = CMN_ERR_NOT_FOUND;
    uint32_t cnt = 0;
    uint32_t i = 0;
    uint8_t  str_wk[20] = { 0 };

    do
    {
        if ((NULL == p_buff) || (0 == size))
        {
            rslt = CMN_ERR_PARAMETER;
            break;
        }

        rslt = r_cmn_uint64_to_str_cnv(str_wk, sizeof(str_wk), dat, flag);
        if (0 > rslt)
        {
            break;
        }
        else
        {
            cnt = rslt;
        }

        width = r_cmn_int_to_str_padding_size(size, width, cnt, flag);

        rslt = r_cmn_int_to_str_put_padding_and_header(
                p_buff, size, width, flag);
        if (0 > rslt)
        {
            break;
        }

        p_buff += rslt;

        for (i=0; cnt > i; i++)
        {
            *p_buff = str_wk[i];
            p_buff++;
        }
        *p_buff = '\0';
        rslt = CMN_NO_ERROR;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_uint64_to_str
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_int64_to_str
 * Description  : convert uint32_t data to string.
 * Arguments    : uint8_t *p_buff : top address for save area.
 *              : uint32_t size   : save area size.
 *              : uint64_t dat    : convert data.
 *              : uint32_t width  : digits number.
 *              : uint32_t flag   : convert information flags.
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
static int32_t r_cmn_int64_to_str(uint8_t *p_buff, uint32_t size, int64_t dat, uint32_t width, uint32_t flag)
{
    int32_t rslt = CMN_ERR_NOT_FOUND;

    do
    {
        if ((0 != (flag & flag_dec)) && (dat < 0))
        {
            flag |= flag_signal_minus;
            dat = -dat;
        }

        /*
         * abs(dat) is in int64_t range.
         * uint64_t range is larger than int64_t range.
         */
        rslt = r_cmn_uint64_to_str(p_buff, size, (uint64_t)dat, width, flag);
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_int64_to_str
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_put_string
 * Description  : output string data
 * Arguments    : uint32_t id       : output port id
 *              : uint8_t *p_buff   : top address for string area.
 *              : uint32_t size     : save area size.
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
static int32_t r_cmn_put_string(uint32_t id, uint8_t *p_buff, uint32_t size)
{
    int32_t rslt = CMN_ERR_NOT_FOUND;

    do
    {
        if (id >= CMN_PRINT_OUT_ID_NUM)
        {
            rslt = CMN_ERR_NOT_EXIST;
            break;
        }
        rslt = gl_printf_out_info[id].pf_puts(p_buff, size);
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_put_string
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: r_cmn_puts_serial
 * Description  : string data out put to serial.
 * Arguments    : uint8_t *p_buff : top address for string area.
 *              : uint32_t size   : save area size.
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
static int32_t r_cmn_puts_serial(uint8_t *p_buff, uint32_t size)
{
    int32_t rslt = CMN_ERR_UNSUPPORTED;

    do
    {
        // rslt = (int32_t)puts_com(R_CMN_SERIAL_ID, (VB *)p_buff, (UINT *)&size, TMO_FEVR);
        if (0 < UART_SendStringPIO(p_buff, size))
        {
            rslt = CMN_NO_ERROR;
        }
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_puts_serial
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_CMN_SetPutsFunc
 * Description  : printf out put function setting.
 * Arguments    : PutsFunc_t *pf : output function pointer
 *              : 
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
int32_t R_CMN_SetPutsFunc(uint32_t id, PutsFunc_t *pf)
{
    int32_t rslt = CMN_ERR_UNSUPPORTED;

    do
    {
        if (id >= CMN_PRINT_OUT_ID_NUM)
        {
            rslt = CMN_ERR_NOT_EXIST;
            break;
        }

        // loc_cpu();
        gl_printf_out_info[id].pf_puts = pf;
        // unl_cpu();
        rslt = CMN_NO_ERROR;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_SetPutsFunc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_CMN_SetPutsFunc4Serial
 * Description  : printf out put function set to serial out.
 * Arguments    : void
 *              : 
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
int32_t R_CMN_SetPutsFunc4Serial(void)
{
    int32_t rslt = CMN_ERR_UNSUPPORTED;

    do
    {
        // loc_cpu();
        gl_printf_out_info[0].pf_puts = r_cmn_puts_serial;
        // unl_cpu();
        rslt = CMN_NO_ERROR;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_SetPutsFunc4Serial
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_cmn_puts_uart_pio
 * Description  : string data out put to uart.
 * Arguments    : uint8_t *p_buff : top address for string area.
 *              : uint32_t size   : save area size.
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
static int32_t r_cmn_puts_uart_pio(uint8_t *p_buff, uint32_t size)
{
    int32_t     rslt    = CMN_ERR_UNSUPPORTED;
    uint32_t    res     = 0;

    do
    {
        res = UART_SendStringPIO(p_buff, size);

        if (res == size)
        {
            rslt = CMN_NO_ERROR;
        }
        else
        {
            rslt = CMN_ERR_OVERFLOW;
        }
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function r_cmn_puts_serial
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_CMN_SetPutsFunc4UARTPIO
 * Description  : printf out put function set to uart pio out.
 * Arguments    : void
 *              : 
 *              : 
 * Return Value : Error Code
 *                CMN_NO_ERROR : safety end.
 *                0 > : error end.
 *********************************************************************************************************************/
int32_t R_CMN_SetPutsFunc4UARTPIO(void)
{
    int32_t rslt = CMN_ERR_PARAMETER;

    do
    {
        // loc_cpu();
        uart_init(0);
        gl_printf_out_info[0].pf_puts = r_cmn_puts_uart_pio;
        // unl_cpu();
        rslt = CMN_NO_ERROR;
    }
    while (0);

    return (rslt);
}
/**********************************************************************************************************************
 End of function R_CMN_SetPutsFunc4UARTPIO
 *********************************************************************************************************************/
