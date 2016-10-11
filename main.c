/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_hd44780.h"
#include "tm_stm32f4_adc.h"
#include <stdio.h>

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
  //Make sure delay timer is on before starting
  RCC_HSEConfig(RCC_HSE_ON);
  while(!RCC_WaitForHSEStartUp());
  /* Initialize USART1 at 9600 baud, TX: PB6, RX: PB7 */
  TM_USART_Init(COM_USART, COM_PINS, 9600);

  STM_EVAL_LEDInit(LED4);
  TM_DELAY_Init();
  TM_ADC_InitADC(ADC1);
  
  /* Put string to USART */
  TM_USART_Puts(COM_USART, "Starting now\n\r");
  /* Enable internal temperature sensor */
  TM_ADC_EnableTSensor();
  /* Initialize ADC1 on channel 0(POTENTIOMETER), this is pin PA0 */
  TM_ADC_Init(POT_ADC, POT_CHANNEL);
  /* Initialize ADC1 on channel 2(external thermometer), this is pin PA2 */
  TM_ADC_Init(TEMP_ADC, TEMP_CHANNEL);

  //Initialize LCD
  TM_HD44780_Init(16, 2);
  //Put string to LCD
  TM_HD44780_Puts(0, 0, "STM32F4/29 Discovery");
  //Wait a little
  Delayms(3000);
  //Clear LCD
  TM_HD44780_Clear();
  //Show cursor
  TM_HD44780_CursorOn();
  //Write new text
  TM_HD44780_Puts(6, 0, "CLEARED!");
  //Wait a little
  Delayms(1000);
  //Enable cursor blinking
  TM_HD44780_BlinkOn();
  
  char str[15];
  uint32_t potentiometer;
  uint16_t thermometer;
  int timing = 0;
  while (1) {
    potentiometer = TM_ADC_Read(POT_ADC, POT_CHANNEL);
    /* 3.3 v max, 1000 to convert to mV, 4096 = 2^12 sample number */
    potentiometer = potentiometer * 1000 * 3.3/ 4096;
    
    thermometer = TM_ADC_Read(TEMP_ADC, TEMP_CHANNEL);
    
    /* 100ms delay */
    Delayms(100);
    timing++;
    
    //Once a second
    if(timing==10) {
      /*  Make a string for USART to send */
      sprintf(str, "PV: %4d mV, TIN:%4d c, TOUT:%4d c\n\r", 
             (uint16_t)potentiometer, TM_ADC_ReadIntTemp(ADC1), thermometer);
      /* Flash LED to confirm program isn't hanging */
      STM_EVAL_LEDToggle(LED4);
      /* Put to COM */
      TM_USART_Puts(COM_USART, str);
      /* Put on LCD */
      TM_HD44780_Puts(0, 0, str);
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