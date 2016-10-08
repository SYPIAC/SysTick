/**
  ******************************************************************************
  * @file    SysTick/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_hd44780.h"
#include "tm_stm32f4_adc.h"
#include<stdio.h>

 

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup SysTick_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */     
  
    /* Initialize USART1 at 9600 baud, TX: PB6, RX: PB7 */
    TM_USART_Init(USART1, TM_USART_PinsPack_2, 9600);
    
    STM_EVAL_LEDInit(LED4);
    TM_DELAY_Init();
    TM_ADC_InitADC(ADC1);
    
    /* Put string to USART */
    TM_USART_Puts(USART1, "Starting now\n\r");
    /* Enable internal temperature sensor */
    TM_ADC_EnableTSensor();
    /* Initialize ADC1 on channel 0(POTENTIOMETER), this is pin PA0 */
    TM_ADC_Init(ADC1, ADC_Channel_0);
    /* Initialize ADC1 on channel 1(external thermometer), this is pin PA1 */
    TM_ADC_Init(ADC1, ADC_Channel_2);
    
    char str[15];
    uint32_t potentiometer;
    uint16_t thermometer;
    int timing = 0;
    while (1) {
        potentiometer = TM_ADC_Read(ADC1, ADC_Channel_0);
        //5 v max, 1000 to convert to mV, 4096 = 2^12 sample number
        potentiometer = potentiometer * 1000 * 3.3/ 4096;
        
        thermometer = TM_ADC_Read(ADC1, ADC_Channel_2);
        
        /* 100ms delay */
        Delayms(100);
        timing++;
        
        //Once a second
        if(timing==10) {
          /*  Make  a string for USART to send */
          sprintf(str, "PV: %4d mV, TIN:%4d c, TOUT:%4d c\n\r", 
                 (uint16_t)potentiometer, TM_ADC_ReadIntTemp(ADC1), thermometer);
          /*Flash LED to confirm program isn't hanging*/
          STM_EVAL_LEDToggle(LED4);
          /* Put to USART */
          TM_USART_Puts(USART1, str);
          
          timing = 0;
        }        
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
