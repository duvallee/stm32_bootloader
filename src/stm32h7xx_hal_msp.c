/**
  ******************************************************************************
  * File Name          : stm32h7xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
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

extern void _Error_Handler(char *, int);

/* --------------------------------------------------------------------------
 * Name : HAL_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_MspInit(void)
{
   __HAL_RCC_SYSCFG_CLK_ENABLE();

   HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

   // System interrupt init
   // MemoryManagement_IRQn interrupt configuration
   HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);

   // BusFault_IRQn interrupt configuration
   HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);

   // UsageFault_IRQn interrupt configuration
   HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

   // SVCall_IRQn interrupt configuration
   HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);

   // DebugMonitor_IRQn interrupt configuration
   HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);

   // PendSV_IRQn interrupt configuration
   HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);

   // SysTick_IRQn interrupt configuration
   HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/* --------------------------------------------------------------------------
 * Name : HAL_ADC_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
   if (hadc->Instance == ADC1)
   {
      __HAL_RCC_ADC12_CLK_ENABLE();
      __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_CLKP);

      // ADC1 GPIO Configuration
      // PA0_C     ------> ADC1_INP0
      HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_OPEN);
   }
}

/* --------------------------------------------------------------------------
 * Name : HAL_ADC_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
   if (hadc->Instance == ADC1)
   {
      // Peripheral clock disable
      __HAL_RCC_ADC12_CLK_DISABLE();
   }
}


/* --------------------------------------------------------------------------
 * Name : HAL_I2C_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
   GPIO_InitTypeDef GPIO_InitStruct;
   if (hi2c->Instance == I2C1)
   {
      // Peripheral clock enable
      __HAL_RCC_I2C1_CLK_ENABLE();

      __HAL_RCC_GPIOB_CLK_ENABLE();
      // I2C1 GPIO Configuration    
      // PB6     ------> I2C1_SCL
      // PB7     ------> I2C1_SDA 
      GPIO_InitStruct.Pin                                = GPIO_PIN_6 | GPIO_PIN_7;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_OD;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Speed                              = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate                          = GPIO_AF4_I2C1;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   }
}

/* --------------------------------------------------------------------------
 * Name : HAL_I2C_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
   if (hi2c->Instance == I2C1)
   {
      /* Peripheral clock disable */
      __HAL_RCC_I2C1_CLK_DISABLE();

      /**I2C1 GPIO Configuration    
      PB6     ------> I2C1_SCL
      PB7     ------> I2C1_SDA 
      */
      HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
   }
}

/* --------------------------------------------------------------------------
 * Name : HAL_HCD_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
{
   GPIO_InitTypeDef GPIO_InitStruct;

   if (hpcd->Instance == USB1_OTG_HS)
   {
      // Configure USB HS GPIOs
      __GPIOA_CLK_ENABLE();
      __GPIOB_CLK_ENABLE();
      __GPIOC_CLK_ENABLE();
      __GPIOH_CLK_ENABLE();
      __GPIOI_CLK_ENABLE();

      // ULPI - CLK
      GPIO_InitStruct.Pin                                = GPIO_PIN_5;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Speed                              = GPIO_SPEED_FREQ_VERY_HIGH;
      GPIO_InitStruct.Alternate                          = GPIO_AF10_OTG2_HS;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      // ULPI - D0
      GPIO_InitStruct.Pin                                = GPIO_PIN_3;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Speed                              = GPIO_SPEED_FREQ_VERY_HIGH;
      GPIO_InitStruct.Alternate                          = GPIO_AF10_OTG2_HS;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      // ULPI - D1 D2 D3 D4 D5 D6 D7
      GPIO_InitStruct.Pin                                = GPIO_PIN_0      |
                                                           GPIO_PIN_1      |
                                                           GPIO_PIN_5      |
                                                           GPIO_PIN_10     |
                                                           GPIO_PIN_11     |
                                                           GPIO_PIN_12     |
                                                           GPIO_PIN_13;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Alternate                          = GPIO_AF10_OTG2_HS;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

      // ULPI - STP
      GPIO_InitStruct.Pin                                = GPIO_PIN_0;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Alternate                          = GPIO_AF10_OTG2_HS;
      HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

      // ULPI - NXT
      GPIO_InitStruct.Pin                                = GPIO_PIN_4;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Alternate                          = GPIO_AF10_OTG2_HS;
      HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

      // ULPI - DIR
      GPIO_InitStruct.Pin                                = GPIO_PIN_11;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Alternate                          = GPIO_AF10_OTG2_HS;
      HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
      __HAL_RCC_USB1_OTG_HS_ULPI_CLK_ENABLE();

      // Enable USB HS Clocks
      __HAL_RCC_USB1_OTG_HS_CLK_ENABLE();

      // Set USBHS Interrupt priority
      HAL_NVIC_SetPriority(OTG_HS_IRQn, 1, 0);

      // Enable USBHS Interrupt
      HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
   }
}


/* --------------------------------------------------------------------------
 * Name : HAL_PCD_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_PCD_MspDeInit(PCD_HandleTypeDef * hpcd)
{
   if (hpcd->Instance == USB1_OTG_HS)
   {
      /* Disable USB HS Clocks */
      __HAL_RCC_USB1_OTG_HS_CLK_DISABLE();
      __HAL_RCC_USB1_OTG_HS_ULPI_CLK_DISABLE();
   }
}

/* --------------------------------------------------------------------------
 * Name : USER_Debug_UART_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
__weak void USER_Debug_UART_MspInit(UART_HandleTypeDef *huart)
{
   UNUSED(huart);
}
/* --------------------------------------------------------------------------
 * Name : HAL_UART_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
   GPIO_InitTypeDef GPIO_InitStruct;
   if (huart->Instance == USART1)
   {
      USER_Debug_UART_MspInit(huart);
   }
   else if (huart->Instance == USART2)
   {
      /* Peripheral clock enable */
      __HAL_RCC_USART2_CLK_ENABLE();

      /**USART2 GPIO Configuration    
      PA2     ------> USART2_TX
      PA1     ------> USART2_RTS
      PA3     ------> USART2_RX 
      */
      GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_3;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
   }
   else if (huart->Instance == USART3)
   {
      /* Peripheral clock enable */
      __HAL_RCC_USART3_CLK_ENABLE();

      /**USART3 GPIO Configuration    
      PB10     ------> USART3_TX
      PB11     ------> USART3_RX 
      */
      GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
   }
}

/* --------------------------------------------------------------------------
 * Name : HAL_UART_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
   if (huart->Instance == USART1)
   {
   }
   else if (huart->Instance == USART2)
   {
      /* Peripheral clock disable */
      __HAL_RCC_USART2_CLK_DISABLE();

      /**USART2 GPIO Configuration    
      PA2     ------> USART2_TX
      PA1     ------> USART2_RTS
      PA3     ------> USART2_RX 
      */
      HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_3);
   }
   else if (huart->Instance == USART3)
   {
      /* Peripheral clock disable */
      __HAL_RCC_USART3_CLK_DISABLE();

      /**USART3 GPIO Configuration    
      PB10     ------> USART3_TX
      PB11     ------> USART3_RX 
      */
      HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);
   }
}

#if 0
/* --------------------------------------------------------------------------
 * Name : HAL_PCD_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
{
   GPIO_InitTypeDef GPIO_InitStruct;
   if (hpcd->Instance == USB_OTG_HS)
   {
      /**USB_OTG_HS GPIO Configuration    
      PB15     ------> USB_OTG_HS_DP
      PB14     ------> USB_OTG_HS_DM 
      */
      GPIO_InitStruct.Pin                                = GPIO_PIN_15 | GPIO_PIN_14;
      GPIO_InitStruct.Mode                               = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull                               = GPIO_NOPULL;
      GPIO_InitStruct.Speed                              = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate                          = GPIO_AF12_OTG2_FS;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

      /* Peripheral clock enable */
      __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
   }
}

/* --------------------------------------------------------------------------
 * Name : HAL_PCD_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_PCD_MspDeInit(PCD_HandleTypeDef* hpcd)
{
   if (hpcd->Instance == USB_OTG_HS)
   {
      /* Peripheral clock disable */
      __HAL_RCC_USB_OTG_HS_CLK_DISABLE();

      /**USB_OTG_HS GPIO Configuration    
      PB15     ------> USB_OTG_HS_DP
      PB14     ------> USB_OTG_HS_DM 
      */
      HAL_GPIO_DeInit(GPIOB, GPIO_PIN_15|GPIO_PIN_14);
   }
}
#endif

/* --------------------------------------------------------------------------
 * Name : HAL_FMC_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
static int g_fmc_initialized                             = 0;
static void HAL_FMC_MspInit(void)
{
   GPIO_InitTypeDef gpio_init_structure;

   debug_output_info("FMC_Initialized : %d \r\n", g_fmc_initialized);

   if (g_fmc_initialized)
   {
      return;
   }
   g_fmc_initialized                                     = 1;

   // Enable FMC clock
   __HAL_RCC_FMC_CLK_ENABLE();

   // Enable chosen DMAx clock
   __HAL_RCC_MDMA_CLK_ENABLE();

   // Enalbe GPIOx clock
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_GPIOE_CLK_ENABLE();
   __HAL_RCC_GPIOF_CLK_ENABLE();
   __HAL_RCC_GPIOG_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOI_CLK_ENABLE();

   // ------------------------------------------------------------------------
   // GPIOC configuration (PC8, FMC_NE2 (Enable 2))
   gpio_init_structure.Pin                               = GPIO_PIN_8;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_PULLUP;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF9_FMC;
   HAL_GPIO_Init(GPIOC, &gpio_init_structure);


   // ------------------------------------------------------------------------
   // GPIOD configuration (PD4 : NOE(Output Enable, NRE), PD5 : FMC_NWE(Write Enable)), PD7 : (Enable 1))

   gpio_init_structure.Pin                               = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_PULLUP;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOD, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOD configuration (PD0 : D2, PD1 : D3, PD8 : D13, PD9 : D14, PD10 : D15, PD14 : D0, PD15 : D1)

   gpio_init_structure.Pin                               = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_NOPULL;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOD, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOE configuration (PE0 : NBL0(Output Byte Mask for write accesses), PE1 : NBL1(Output Byte Mask for write accesses))

   gpio_init_structure.Pin                               = GPIO_PIN_0 | GPIO_PIN_1;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_PULLUP;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOE, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOE configuration (PE2 ~ PE6 : A23, A19, A29, A21, A22)
   //                     (PE7 ~ PE15 : D4 ~ D12)

   gpio_init_structure.Pin                               =  GPIO_PIN_2 |  GPIO_PIN_3 |  GPIO_PIN_4 |  GPIO_PIN_5 |  GPIO_PIN_6 |
                                                            GPIO_PIN_7 |  GPIO_PIN_8 |  GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
                                                           GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_NOPULL;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOE, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOF configuration (PF11 : FMC_SDNRAS)

   gpio_init_structure.Pin                               = GPIO_PIN_11;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_PULLUP;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOF, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOF configuration (PF0 ~ PF5 : A0 ~ A5)
   //                     (PE12 ~ PE15 : A6 ~ A9)

   gpio_init_structure.Pin                               =  GPIO_PIN_0 |  GPIO_PIN_1 |  GPIO_PIN_2 |  GPIO_PIN_3 |  GPIO_PIN_4 |
                                                            GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_NOPULL;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOF, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOG configuration (PG15 : FMC_SDNCAS)

   gpio_init_structure.Pin                               = GPIO_PIN_15;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_PULLUP;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOG, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOG configuration (PG0 ~ PG5 : A10 ~ A15) - PG3 (A13, Not used), PG4 ~ PG5 (Bank Address of SDRAM)
   //                     (PG8 : FMC_SDCLK)

   gpio_init_structure.Pin                               = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_NOPULL;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOG, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOH configuration (PH5 : FMC_SDNWE, PH6 : FMCSDNE1, PH7 : FMC_SDCKE1)

   gpio_init_structure.Pin                               = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_PULLUP;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOH, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOH configuration (PH8 ~ PH15 : D16 ~ D23)

   gpio_init_structure.Pin                               = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_NOPULL;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOH, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOI configuration (PI4 : FMC_NBL2, PI5 : FMC_NBL3)

   gpio_init_structure.Pin                               = GPIO_PIN_4 | GPIO_PIN_5;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_PULLUP;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOI, &gpio_init_structure);

   // ------------------------------------------------------------------------
   // GPIOI configuration (PI0 ~ PI3 : D24 ~ D27)
   //                     (PI6 : D28, PI7 : D29)
   //                     (PI9 : D30, PI10 : D31)

   gpio_init_structure.Pin                               = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                                                           GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_NOPULL;
   gpio_init_structure.Speed                             = GPIO_SPEED_FREQ_VERY_HIGH;
   gpio_init_structure.Alternate                         = GPIO_AF12_FMC;
   HAL_GPIO_Init(GPIOI, &gpio_init_structure);

}

/* --------------------------------------------------------------------------
 * Name : HAL_SRAM_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_SRAM_MspInit(SRAM_HandleTypeDef* hsram)
{
   HAL_FMC_MspInit();
}

/* --------------------------------------------------------------------------
 * Name : HAL_SDRAM_MspInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram)
{
   HAL_FMC_MspInit();
}

/* --------------------------------------------------------------------------
 * Name : HAL_FMC_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
static void HAL_FMC_MspDeInit(void)
{
}

/* --------------------------------------------------------------------------
 * Name : HAL_SRAM_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef* hsram)
{
   HAL_FMC_MspDeInit();
}

/* --------------------------------------------------------------------------
 * Name : HAL_SDRAM_MspDeInit()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram)
{
   HAL_FMC_MspDeInit();
}

