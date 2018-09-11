/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
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

#include "main.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx.h"
#include "stm32h7xx_it.h"

// External variables --------------------------------------------------------

// ******************************************************************************
// *            Cortex Processor Interruption and Exception Handlers
// ******************************************************************************

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
   _Error_Handler(__FILE__, __LINE__);
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
   _Error_Handler(__FILE__, __LINE__);
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
   _Error_Handler(__FILE__, __LINE__);
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
   _Error_Handler(__FILE__, __LINE__);
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
}


/* --------------------------------------------------------------------------
 * Name : debug_tick_timer_handler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void debug_tick_timer_handler()
{
}

/* --------------------------------------------------------------------------
 * Name : power_tick_timer_handler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void power_tick_timer_handler()
{
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
   debug_tick_timer_handler();
   power_tick_timer_handler();

   HAL_IncTick();
   HAL_SYSTICK_IRQHandler();
}

/* --------------------------------------------------------------------------
 * Name : User_EXTI0_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void User_EXTI0_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : EXTI0_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void EXTI0_IRQHandler()
{
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
   User_EXTI0_IRQHandler();
}

/* --------------------------------------------------------------------------
 * Name : User_EXTI1_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void User_EXTI1_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : EXTI1_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void EXTI1_IRQHandler(void)
{
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
   User_EXTI1_IRQHandler();
}

/* --------------------------------------------------------------------------
 * Name : User_EXTI2_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void User_EXTI2_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : EXTI2_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void EXTI2_IRQHandler(void)
{
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
   User_EXTI2_IRQHandler();
}

/* --------------------------------------------------------------------------
 * Name : Start_button_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void Start_button_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : EXTI3_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void EXTI3_IRQHandler(void)
{
   Start_button_IRQHandler();
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

/* --------------------------------------------------------------------------
 * Name : Power_Switch_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void Power_Switch_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : ADC2_Busy_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void ADC2_Busy_IRQHandler()
{
}


/* --------------------------------------------------------------------------
 * Name : EXTI4_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void EXTI4_IRQHandler(void)
{
  Power_Switch_IRQHandler();
#if 0
   ADC2_Busy_IRQHandler();
#endif
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

/* --------------------------------------------------------------------------
 * Name : EXTI9_5_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void EXTI9_5_IRQHandler(void)
{
   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
   }
}

/* --------------------------------------------------------------------------
 * Name : USB_VBUS_Detect_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void USB_VBUS_Detect_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : ADC2_Busy_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void ADC1_Busy_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : User_EXTI13_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void User_EXTI13_IRQHandler()
{
}

/* --------------------------------------------------------------------------
 * Name : EXTI15_10_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void EXTI15_10_IRQHandler(void)
{
   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != 0)
   {
      USB_VBUS_Detect_IRQHandler();
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != 0)
   {
#if 0
      ADC1_Busy_IRQHandler();
#endif
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != 0)
   {
      User_EXTI13_IRQHandler();
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
   }
}


/* --------------------------------------------------------------------------
 * Name : USB_CDC_HS_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void USB_CDC_HS_IRQHandler(void)
{
}

/* --------------------------------------------------------------------------
 * Name : OTG_HS_IRQHandler()
 *
 *
 * -------------------------------------------------------------------------- */
void OTG_HS_IRQHandler(void)
{
   USB_CDC_HS_IRQHandler();
}


