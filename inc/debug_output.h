/*
 *  File: debug_output.h
 *
 * COPYRIGHT(c) 2018 MICROVISION Co., Ltd.
 *
*/

#ifndef __DEBUG_OUTPUT_H__
#define __DEBUG_OUTPUT_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "printf.h"

#if defined(UART_DEBUG_OUTPUT)
#define DEBUG_STRING_LEVEL_ERROR
#define DEBUG_STRING_LEVEL_WARN
#define DEBUG_STRING_LEVEL_DEBUG
#define DEBUG_STRING_LEVEL_FN_TRACE
#define DEBUG_STRING_LEVEL_INFO
#define DEBUG_STRING_LEVEL_DUMP
#else
#undef DEBUG_STRING_LEVEL_ERROR
#undef DEBUG_STRING_LEVEL_WARN
#undef DEBUG_STRING_LEVEL_DEBUG
#undef DEBUG_STRING_LEVEL_FN_TRACE
#undef DEBUG_STRING_LEVEL_INFO
#undef DEBUG_STRING_LEVEL_DUMP
#endif

#if defined(DEBUG_STRING_LEVEL_ERROR)
#define debug_output_error(fmt, ...)                                             \
         printf("[%06d.%03d:%s-%s-%d-ERROR] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_error(fmt, ...)         asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_WARN)
#define debug_output_warn(fmt, ...)                                              \
         printf("[%06d.%03d:%s-%s-%d-WARN ] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_warn(fmt, ...)          asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_DEBUG)
#define debug_output_debug(fmt, ...)                                             \
         printf("[%06d.%03d:%s-%s-%d-DEBUG] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_debug(fmt, ...)         asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_FN_TRACE)
#define debug_output_fn(fmt, ...)                                                \
         printf("[%06d.%03d:%s-%s-%d-FN   ] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_fn(fmt, ...)            asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_INFO)
#define debug_output_info(fmt, ...)                                              \
         printf("[%06d.%03d:%s-%s-%d-INFO ] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_info(fmt, ...)          asm("nop")
#endif


#if defined(DEBUG_STRING_LEVEL_DUMP)
#define debug_output_dump(fmt, ...)          printf(fmt, ##__VA_ARGS__)
#else
#define debug_output_dump(fmt, ...)          asm("nop")
#endif

extern volatile unsigned int g_System_Start_Second;
extern volatile unsigned int g_System_Start_Milli_Second;

#ifdef __cplusplus
}
#endif

#endif      // __PRINTF_H__

