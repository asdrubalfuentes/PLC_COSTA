/*
 * main.h
 *
 *  Created on: Oct 26, 2024
 *      Author: Asdrubal_Fuentes
 */

#ifndef USER_MAIN_H_
#define USER_MAIN_H_
/*          GPIOA               */
#define AI1             GPIO_Pin_0
#define AI2             GPIO_Pin_1
#define CS_WINBOND      GPIO_Pin_2
#define AI3             GPIO_Pin_3
#define AI4             GPIO_Pin_4
#define CLK_WINBOND     GPIO_Pin_5
#define MOSI_WINBOND    GPIO_Pin_6
#define MISO_WINBOND    GPIO_Pin_7
#define AO1             GPIO_Pin_8
#define USART1_TX       GPIO_Pin_9
#define USART1_RX       GPIO_Pin_10
#define USB1_DN         GPIO_Pin_11
#define USB1_DP         GPIO_Pin_12
#define SWDIO           GPIO_Pin_13
#define SWCLK           GPIO_Pin_14
#define LED1            GPIO_Pin_15
/*          GPIOB               */
#define AI5             GPIO_Pin_0
#define AI6             GPIO_Pin_1
#define BOOT1           GPIO_Pin_2
#define USR_BTT         GPIO_Pin_3
#define LED2            GPIO_Pin_4
#define AO2             GPIO_Pin_5
#define USB2_DN         GPIO_Pin_6
#define USB2_DP         GPIO_Pin_7
#define DI1             GPIO_Pin_8
#define DI2             GPIO_Pin_9
#define SCL_FT24C32A    GPIO_Pin_10
#define SDA_FT24C32A    GPIO_Pin_11
#define DI3             GPIO_Pin_12
#define DI4             GPIO_Pin_13
#define DI5             GPIO_Pin_14
#define DI6             GPIO_Pin_15
/*          GPIOC               */
#define LINK_LED        GPIO_Pin_0
#define ACT_LED         GPIO_Pin_1
#define DI7             GPIO_Pin_2
#define DI8             GPIO_Pin_3
#define DI9             GPIO_Pin_4
#define DI10            GPIO_Pin_5
#define RXP_ETH         GPIO_Pin_6
#define RXN_ETH         GPIO_Pin_7
#define TXP_ETH         GPIO_Pin_8
#define D0_SD           GPIO_Pin_8
#define TXN_ETH         GPIO_Pin_9
#define D1_SD           GPIO_Pin_9
#define D2_SD           GPIO_Pin_10
#define D3_SD           GPIO_Pin_11
#define CLK_SD          GPIO_Pin_12
#define DI11            GPIO_Pin_13
#define OSC_RTC_IN      GPIO_Pin_14
#define OSC_RTC_OUT     GPIO_Pin_15
/*          GPIOD               */
#define DI12            GPIO_Pin_0
#define DI13            GPIO_Pin_1
#define CMD_SD          GPIO_Pin_2
#define DI14            GPIO_Pin_3
#define DI15            GPIO_Pin_4
#define DI16            GPIO_Pin_5
#define DI17            GPIO_Pin_6
#define TFSW_SD         GPIO_Pin_7
#define DO1             GPIO_Pin_8
#define DO2             GPIO_Pin_9
#define DO3             GPIO_Pin_10
#define DO4             GPIO_Pin_11
#define DO5             GPIO_Pin_12
#define DO6             GPIO_Pin_13
#define DO7             GPIO_Pin_14
#define DO8             GPIO_Pin_15
/*          GPIOE               */
#define DO9             GPIO_Pin_0
#define DO10            GPIO_Pin_1
#define DO11            GPIO_Pin_2
#define DO12            GPIO_Pin_3
#define DO13            GPIO_Pin_4
#define DO14            GPIO_Pin_5
#define DO15            GPIO_Pin_6
#define DO16            GPIO_Pin_7
#define DO17            GPIO_Pin_8
#define DO18            GPIO_Pin_9
#define DO19            GPIO_Pin_10
#define DO20            GPIO_Pin_11
#define DO21            GPIO_Pin_12
#define DO22            GPIO_Pin_13
#define DO23            GPIO_Pin_14
#define DO24            GPIO_Pin_15

#endif /* USER_MAIN_H_ */
