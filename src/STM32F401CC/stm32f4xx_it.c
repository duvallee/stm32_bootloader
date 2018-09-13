/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

// ******************************************************************************
//            Cortex-M4 Processor Interruption and Exception Handlers
// ******************************************************************************

// ***************************************************************************
// Fuction      : debug_tick_timer_handler()
// Description  : 
// 
//
// ***************************************************************************
__weak void debug_tick_timer_handler()
{
}

// ***************************************************************************
// Fuction      : debug_tick_timer_handler()
// Description  : 
// 
//
// ***************************************************************************
__weak void led_tick_timer_handler()
{
}


// ***************************************************************************
// Fuction      : led_tick_timer_handler()
// Description  : 
// 
//
// ***************************************************************************
void SysTick_Handler(void)
{
   HAL_IncTick();
   HAL_SYSTICK_IRQHandler();
   debug_tick_timer_handler();
   led_tick_timer_handler();
}

// ******************************************************************************
// STM32F4xx Peripheral Interrupt Handlers
// Add here the Interrupt Handlers for the used peripherals
// For the available peripheral interrupt handler names,
// please refer to the startup file (startup_stm32f4xx.s).
// ******************************************************************************

// ***************************************************************************
// Fuction      : USB_BULK_FS_IRQHandler()
// Description  : 
// 
//
// ***************************************************************************
__weak void USB_BULK_FS_IRQHandler(void)
{
}

// ***************************************************************************
// Fuction      : OTG_FS_IRQHandler()
// Description  : 
// 
//
// ***************************************************************************
void OTG_FS_IRQHandler(void)
{
   USB_BULK_FS_IRQHandler();
}


