/*
 *  File: printf.h
 *
 * COPYRIGHT(c) 2018 MICROVISION Co., Ltd.
 *
*/

#ifndef __PRINTF_H__
#define __PRINTF_H__

#ifdef __cplusplus
extern "C" {
#endif 

#if defined(UART_DEBUG_OUTPUT)

#pragma once
#include <stdarg.h>

// #define printf                                           tfp_printf
// int tfp_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif      // UART_DEBUG_OUTPUT

#endif      // __PRINTF_H__

