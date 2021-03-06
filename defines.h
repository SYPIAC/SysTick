/**
 *  Defines for your entire project at one place
 * 
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/*==================== 
 Delay timer
======================*/
#define TM_DELAY_TIM				TIM2
#define TM_DELAY_TIM_IRQ			TIM2_IRQn
#define TM_DELAY_TIM_IRQ_HANDLER	TIM2_IRQHandler

/*==================== 
 COM PORT
======================*/
#define COM_USART USART1
//Look in tm_stm32f4_usart.h for what pin packs correspond to what pins
#define COM_PINS TM_USART_PinsPack_2
/*==================== 
 ADC Channels
======================*/
//For potentiometer
#define POT_ADC ADC1
#define POT_CHANNEL ADC_Channel_0
//For temperature sensor
#define TEMP_ADC ADC1
#define TEMP_CHANNEL ADC_Channel_2
/*==================== 
 HD44780 Control pins
======================*/
/* RS - Register select pin */
//#define HD44780_RS_PORT			GPIOB
//#define HD44780_RS_PIN			GPIO_Pin_2
/* E - Enable pin */
//#define HD44780_E_PORT			GPIOB
//#define HD44780_E_PIN				GPIO_Pin_7

/* D4 - Data 4 pin */
//#define HD44780_D4_PORT			GPIOC
//#define HD44780_D4_PIN			GPIO_Pin_12
/* D5 - Data 5 pin */
//#define HD44780_D5_PORT			GPIOC
//#define HD44780_D5_PIN			GPIO_Pin_13
/* D6 - Data 6 pin */
//#define HD44780_D6_PORT			GPIOB
//#define HD44780_D6_PIN			GPIO_Pin_12
/* D7 - Data 7 pin */
//#define HD44780_D7_PORT			GPIOB
//#define HD44780_D7_PIN			GPIO_Pin_13
/* Put your global defines for all libraries here used in your project */

#endif