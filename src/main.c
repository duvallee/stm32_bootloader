/*
 *  File: main.c
 *
 * Written by duvallee.lee in 2018
 *
 */

#include "main.h"


// ==========================================================================
#define POWER_ON_CHECK_TIMER_CYCLE                       3000

// ==========================================================================
static volatile int delay_count                          = 0;

/* --------------------------------------------------------------------------
 * Name : ns_10_delay()
 *
 *
 * -------------------------------------------------------------------------- */
void ns_10_delay(int n_10_sec)
{
   int i;
   int j;
   for (i = 0; i < n_10_sec; i++)
   {
      for(j = 0; j < 3; j++)
      {
         delay_count                                     = j;
      }
   }
}

/* --------------------------------------------------------------------------
 * Name : us_delay()
 *
 *
 * -------------------------------------------------------------------------- */
void us_delay(int usec)
{
   int i;
   int j;
   for (i = 0; i < usec; i++)
   {
      for(j = 0; j < 196; j++)
      {
         delay_count                                     = j;
      }
   }
}

/* --------------------------------------------------------------------------
 * Name : ms_delay()
 *
 *
 * -------------------------------------------------------------------------- */
void ms_delay(int msec)
{
   int i;
   int j;
   for (i = 0; i < msec; i++)
   {
      for(j = 0; j < 200000; j++)
      {
         delay_count                                     = j;
      }
   }
}

#if 0
/* --------------------------------------------------------------------------
 * Name : MPU_Config
 *
 *  @brief  Configure the MPU attributes as Write Through for SRAM1/2.
 *  @note   The Base Address is 0x24000000 since this memory interface is the AXI.
 *          The Region Size is 512KB, it is related to D1-AXI SRAM memory size.
 *  @param  None
 *  @retval None
 *
 * -------------------------------------------------------------------------- */
void MPU_Config(void)
{
   MPU_Region_InitTypeDef MPU_InitStruct;

   /* Disable the MPU */
   HAL_MPU_Disable();

   // Configure the MPU attributes as WT for SRAM
   MPU_InitStruct.Enable                                 = MPU_REGION_ENABLE;
   MPU_InitStruct.BaseAddress                            = 0x24000000;
   MPU_InitStruct.Size                                   = MPU_REGION_SIZE_512KB;
   MPU_InitStruct.AccessPermission                       = MPU_REGION_FULL_ACCESS;
   MPU_InitStruct.IsBufferable                           = MPU_ACCESS_NOT_BUFFERABLE;
   MPU_InitStruct.IsCacheable                            = MPU_ACCESS_CACHEABLE;
   MPU_InitStruct.IsShareable                            = MPU_ACCESS_NOT_SHAREABLE;
   MPU_InitStruct.Number                                 = MPU_REGION_NUMBER0;
   MPU_InitStruct.TypeExtField                           = MPU_TEX_LEVEL0;
   MPU_InitStruct.SubRegionDisable                       = 0x00;
   MPU_InitStruct.DisableExec                            = MPU_INSTRUCTION_ACCESS_ENABLE;
   HAL_MPU_ConfigRegion(&MPU_InitStruct);

   // Configure the MPU attributes as WT for SDRAM
   MPU_InitStruct.Enable                                 = MPU_REGION_ENABLE;
   MPU_InitStruct.BaseAddress                            = SDRAM_DEVICE_ADDR;
   MPU_InitStruct.Size                                   = MPU_REGION_SIZE_32MB;
   MPU_InitStruct.AccessPermission                       = MPU_REGION_FULL_ACCESS;
   MPU_InitStruct.IsBufferable                           = MPU_ACCESS_NOT_BUFFERABLE;
   MPU_InitStruct.IsCacheable                            = MPU_ACCESS_CACHEABLE; 
   MPU_InitStruct.IsShareable                            = MPU_ACCESS_NOT_SHAREABLE;
   MPU_InitStruct.Number                                 = MPU_REGION_NUMBER1;
   MPU_InitStruct.TypeExtField                           = MPU_TEX_LEVEL0;
   MPU_InitStruct.SubRegionDisable                       = 0x00;
   MPU_InitStruct.DisableExec                            = MPU_INSTRUCTION_ACCESS_DISABLE;
   HAL_MPU_ConfigRegion(&MPU_InitStruct);

   // Configure the MPU attributes as WT for QSPI
   MPU_InitStruct.Enable                                 = MPU_REGION_ENABLE;
   MPU_InitStruct.BaseAddress                            = 0x90000000;
   MPU_InitStruct.Size                                   = MPU_REGION_SIZE_256MB;
   MPU_InitStruct.AccessPermission                       = MPU_REGION_FULL_ACCESS;
   MPU_InitStruct.IsBufferable                           = MPU_ACCESS_NOT_BUFFERABLE;
   MPU_InitStruct.IsCacheable                            = MPU_ACCESS_NOT_CACHEABLE;
   MPU_InitStruct.IsShareable                            = MPU_ACCESS_NOT_SHAREABLE;
   MPU_InitStruct.Number                                 = MPU_REGION_NUMBER2;
   MPU_InitStruct.TypeExtField                           = MPU_TEX_LEVEL0;
   MPU_InitStruct.SubRegionDisable                       = 0x00;
   MPU_InitStruct.DisableExec                            = MPU_INSTRUCTION_ACCESS_ENABLE;
   HAL_MPU_ConfigRegion(&MPU_InitStruct);

   // Configure the MPU attributes as WT for QSPI
   MPU_InitStruct.Enable                                 = MPU_REGION_ENABLE;
   MPU_InitStruct.BaseAddress                            = 0x90000000;
   MPU_InitStruct.Size                                   = MPU_REGION_SIZE_128MB;
   MPU_InitStruct.AccessPermission                       = MPU_REGION_FULL_ACCESS;
   MPU_InitStruct.IsBufferable                           = MPU_ACCESS_NOT_BUFFERABLE;
   MPU_InitStruct.IsCacheable                            = MPU_ACCESS_CACHEABLE;
   MPU_InitStruct.IsShareable                            = MPU_ACCESS_NOT_SHAREABLE;
   MPU_InitStruct.Number                                 = MPU_REGION_NUMBER3;
   MPU_InitStruct.TypeExtField                           = MPU_TEX_LEVEL0;
   MPU_InitStruct.SubRegionDisable                       = 0x00;
   MPU_InitStruct.DisableExec                            = MPU_INSTRUCTION_ACCESS_ENABLE;
   HAL_MPU_ConfigRegion(&MPU_InitStruct);

   // Configure the MPU attributes as WT for ADC1
   MPU_InitStruct.Enable                                 = MPU_REGION_ENABLE;
   MPU_InitStruct.BaseAddress                            = ADC7616_ADC1_DEVICE_ADDR;
   MPU_InitStruct.Size                                   = MPU_REGION_SIZE_32B;
   MPU_InitStruct.AccessPermission                       = MPU_REGION_FULL_ACCESS;
   MPU_InitStruct.IsBufferable                           = MPU_ACCESS_NOT_BUFFERABLE;
   MPU_InitStruct.IsCacheable                            = MPU_ACCESS_NOT_CACHEABLE;
   MPU_InitStruct.IsShareable                            = MPU_ACCESS_NOT_SHAREABLE;
   MPU_InitStruct.Number                                 = MPU_REGION_NUMBER4;
   MPU_InitStruct.TypeExtField                           = MPU_TEX_LEVEL0;
   MPU_InitStruct.SubRegionDisable                       = 0x00;
   MPU_InitStruct.DisableExec                            = MPU_INSTRUCTION_ACCESS_ENABLE;
   HAL_MPU_ConfigRegion(&MPU_InitStruct);

   // Configure the MPU attributes as WT for ADC1
   MPU_InitStruct.Enable                                 = MPU_REGION_ENABLE;
   MPU_InitStruct.BaseAddress                            = ADC7616_ADC2_DEVICE_ADDR;
   MPU_InitStruct.Size                                   = MPU_REGION_SIZE_32B;
   MPU_InitStruct.AccessPermission                       = MPU_REGION_FULL_ACCESS;
   MPU_InitStruct.IsBufferable                           = MPU_ACCESS_NOT_BUFFERABLE;
   MPU_InitStruct.IsCacheable                            = MPU_ACCESS_NOT_CACHEABLE;
   MPU_InitStruct.IsShareable                            = MPU_ACCESS_NOT_SHAREABLE;
   MPU_InitStruct.Number                                 = MPU_REGION_NUMBER5;
   MPU_InitStruct.TypeExtField                           = MPU_TEX_LEVEL0;
   MPU_InitStruct.SubRegionDisable                       = 0x00;
   MPU_InitStruct.DisableExec                            = MPU_INSTRUCTION_ACCESS_ENABLE;
   HAL_MPU_ConfigRegion(&MPU_InitStruct);

   // Enable the MPU
   HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
#endif
/* --------------------------------------------------------------------------
 * Name : CPU_CACHE_Enable()
 *
 *  @ brief  CPU L1-Cache enable.
 *  @ param  None
 *  @ retval None
 *
 * -------------------------------------------------------------------------- */
static void CPU_CACHE_Enable(void)
{
   // Enable I-Cache
   SCB_EnableICache();

   // Enable D-Cache
   SCB_EnableDCache();
}

/* --------------------------------------------------------------------------
 * Name : SystemClock_Config()
 *        System Clock Configuration
 *
 * -------------------------------------------------------------------------- */
void SystemClock_Config(void)
{
   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;
   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

   // Supply configuration update enable 
   MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

   // Configure the main internal regulator output voltage 
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

   while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) 
   {

   }

   // Initializes the CPU, AHB and APB busses clocks 
   RCC_OscInitStruct.OscillatorType                      = RCC_OSCILLATORTYPE_HSE;
   RCC_OscInitStruct.HSEState                            = RCC_HSE_ON;
   RCC_OscInitStruct.HSIState                            = RCC_HSI_OFF;
   RCC_OscInitStruct.CSIState                            = RCC_CSI_OFF;
   RCC_OscInitStruct.PLL.PLLState                        = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource                       = RCC_PLLSOURCE_HSE;

   RCC_OscInitStruct.PLL.PLLM                            = 5;
   RCC_OscInitStruct.PLL.PLLN                            = 160;
   RCC_OscInitStruct.PLL.PLLP                            = 2;
   RCC_OscInitStruct.PLL.PLLR                            = 2;
   RCC_OscInitStruct.PLL.PLLQ                            = 4;

   RCC_OscInitStruct.PLL.PLLVCOSEL                       = RCC_PLL1VCOWIDE;
   RCC_OscInitStruct.PLL.PLLRGE                          = RCC_PLL1VCIRANGE_2;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   // Initializes the CPU, AHB and APB busses clocks 
   RCC_ClkInitStruct.ClockType                           = RCC_CLOCKTYPE_SYSCLK        |
                                                           RCC_CLOCKTYPE_HCLK          |
                                                           RCC_CLOCKTYPE_D1PCLK1       |
                                                           RCC_CLOCKTYPE_PCLK1         |
                                                           RCC_CLOCKTYPE_PCLK2         |
                                                           RCC_CLOCKTYPE_D3PCLK1;
   RCC_ClkInitStruct.SYSCLKSource                        = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.SYSCLKDivider                       = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.AHBCLKDivider                       = RCC_HCLK_DIV2;
   RCC_ClkInitStruct.APB3CLKDivider                      = RCC_APB3_DIV2;
   RCC_ClkInitStruct.APB1CLKDivider                      = RCC_APB1_DIV2;
   RCC_ClkInitStruct.APB2CLKDivider                      = RCC_APB2_DIV2;
   RCC_ClkInitStruct.APB4CLKDivider                      = RCC_APB4_DIV2;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   // activate CSI clock mondatory for I/O Compensation Cell
   __HAL_RCC_CSI_ENABLE() ;

   // Enable SYSCFG clock mondatory for I/O Compensation Cell
   __HAL_RCC_SYSCFG_CLK_ENABLE() ;

   /* Enables the I/O Compensation Cell */    
   HAL_EnableCompensationCell();  

   PeriphClkInitStruct.PeriphClockSelection              = RCC_PERIPHCLK_USART1     |
                                                           RCC_PERIPHCLK_ADC        |
                                                           RCC_PERIPHCLK_I2C1       |
                                                           RCC_PERIPHCLK_USB        |
                                                           RCC_PERIPHCLK_FMC;

   PeriphClkInitStruct.PLL2.PLL2M                        = 2;
   PeriphClkInitStruct.PLL2.PLL2N                        = 12;
   PeriphClkInitStruct.PLL2.PLL2P                        = 1;
   PeriphClkInitStruct.PLL2.PLL2Q                        = 2;
   PeriphClkInitStruct.PLL2.PLL2R                        = 2;
   PeriphClkInitStruct.PLL2.PLL2RGE                      = RCC_PLL2VCIRANGE_3;
   PeriphClkInitStruct.PLL2.PLL2VCOSEL                   = RCC_PLL2VCOMEDIUM;
   PeriphClkInitStruct.PLL2.PLL2FRACN                    = 0;

   // PLL3 for USB Clock
   PeriphClkInitStruct.PLL3.PLL3M                        = 25;
   PeriphClkInitStruct.PLL3.PLL3N                        = 336;
   PeriphClkInitStruct.PLL3.PLL3P                        = 2;
   PeriphClkInitStruct.PLL3.PLL3R                        = 2;
   PeriphClkInitStruct.PLL3.PLL3Q                        = 7;

   PeriphClkInitStruct.FmcClockSelection                 = RCC_FMCCLKSOURCE_D1HCLK;
   PeriphClkInitStruct.Usart16ClockSelection             = RCC_USART16CLKSOURCE_D2PCLK2;
   PeriphClkInitStruct.I2c123ClockSelection              = RCC_I2C123CLKSOURCE_D2PCLK1;
   PeriphClkInitStruct.UsbClockSelection                 = RCC_USBCLKSOURCE_PLL3;
   PeriphClkInitStruct.AdcClockSelection                 = RCC_ADCCLKSOURCE_PLL2;
   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   // Configure the Systick interrupt time 
   HAL_SYSTICK_Config(SystemCoreClock / 1000);

   // Configure the Systick
   HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

   // SysTick_IRQn interrupt configuration
   HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* --------------------------------------------------------------------------
 * Name : debug_break()
 *
 *
 * -------------------------------------------------------------------------- */
int __attribute__ ((noinline)) debug_break(int data)
{
static volatile int debug_break_count                    = 0;
   UNUSED(debug_break_count);

   debug_break_count                                     = data;
   return 0;
}

/* --------------------------------------------------------------------------
 * Name : main()
 *
 *
 * -------------------------------------------------------------------------- */
int main(void)
{
   // Configure the MPU attributes as Write Through
#if 0
   MPU_Config();
#endif

   CPU_CACHE_Enable();

   // Reset of all peripherals, Initializes the Flash interface and the Systick.
   HAL_Init();

   // Configure the system clock
   SystemClock_Config();

#if defined(UART_DEBUG_OUTPUT)
   uart_debug_init();
#endif

   scheduler_init();

   debug_output_info("=============================================== \r\n");
   debug_output_info("%s Ver%d.%d.%d \r\n", PROGRAM_NAME, VERSION_MAIN, VERSION_MINOR, VERSION_SUB);
   debug_output_info("Build Date : %s %s (%s) \r\n", __DATE__, __TIME__, __VERSION__);
   debug_output_info("=============================================== \r\n\r\n");

   while (1)
   {
      scheduler_run();
   }


}


/* --------------------------------------------------------------------------
 * Name : _Error_Handler()
 *
 *
 * -------------------------------------------------------------------------- */
void _Error_Handler(char *file, int line)
{
   // User can add his own implementation to report the HAL error return state
   debug_output_error("Error_Handler() Lock : %s-%d \r\n", file, line);

   while(1)
   {
   }
}

#ifdef  USE_FULL_ASSERT
/* --------------------------------------------------------------------------
 * Name : assert_failed()
 *
 *
 * -------------------------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line)
{ 
   // User can add his own implementation to report the file name and line number,
   // tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)
}
#endif   // USE_FULL_ASSERT


