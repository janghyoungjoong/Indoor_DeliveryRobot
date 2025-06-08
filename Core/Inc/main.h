/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_GPIO_Pin GPIO_PIN_13
#define LED1_GPIO_GPIO_Port GPIOC
#define LED2_GPIO_Pin GPIO_PIN_14
#define LED2_GPIO_GPIO_Port GPIOC
#define AIN1_Pin GPIO_PIN_0
#define AIN1_GPIO_Port GPIOC
#define AIN2_Pin GPIO_PIN_1
#define AIN2_GPIO_Port GPIOC
#define BIN1_Pin GPIO_PIN_2
#define BIN1_GPIO_Port GPIOC
#define BIN2_Pin GPIO_PIN_3
#define BIN2_GPIO_Port GPIOC
#define MD_TIM2_C1_Pin GPIO_PIN_0
#define MD_TIM2_C1_GPIO_Port GPIOA
#define MD_TIM2_C2_Pin GPIO_PIN_1
#define MD_TIM2_C2_GPIO_Port GPIOA
#define TOF1_GPIO_Pin GPIO_PIN_5
#define TOF1_GPIO_GPIO_Port GPIOA
#define US_TIM3_C1_Pin GPIO_PIN_6
#define US_TIM3_C1_GPIO_Port GPIOA
#define TOF2_GPIO_Pin GPIO_PIN_7
#define TOF2_GPIO_GPIO_Port GPIOA
#define US1_TRIG_Pin GPIO_PIN_5
#define US1_TRIG_GPIO_Port GPIOC
#define GPIO1_Pin GPIO_PIN_1
#define GPIO1_GPIO_Port GPIOB
#define GPIO2_Pin GPIO_PIN_13
#define GPIO2_GPIO_Port GPIOB
#define GPIO3_Pin GPIO_PIN_14
#define GPIO3_GPIO_Port GPIOB
#define GPIO4_Pin GPIO_PIN_15
#define GPIO4_GPIO_Port GPIOB
#define US2_TRIG_Pin GPIO_PIN_6
#define US2_TRIG_GPIO_Port GPIOC
#define US2_Echo_Pin GPIO_PIN_8
#define US2_Echo_GPIO_Port GPIOC
#define US2_Echo_EXTI_IRQn EXTI9_5_IRQn
#define US1_Echo_Pin GPIO_PIN_9
#define US1_Echo_GPIO_Port GPIOC
#define US1_Echo_EXTI_IRQn EXTI9_5_IRQn
#define EN_TIM1_C1_Pin GPIO_PIN_8
#define EN_TIM1_C1_GPIO_Port GPIOA
#define EN_TIM1_C2_Pin GPIO_PIN_9
#define EN_TIM1_C2_GPIO_Port GPIOA
#define BT_USART3_TX_Pin GPIO_PIN_10
#define BT_USART3_TX_GPIO_Port GPIOC
#define BT_USART3_RX_Pin GPIO_PIN_11
#define BT_USART3_RX_GPIO_Port GPIOC
#define EN_TIM4_C1_Pin GPIO_PIN_6
#define EN_TIM4_C1_GPIO_Port GPIOB
#define EN_TIM4_C2_Pin GPIO_PIN_7
#define EN_TIM4_C2_GPIO_Port GPIOB
#define TOF_I2C1_SCL_Pin GPIO_PIN_8
#define TOF_I2C1_SCL_GPIO_Port GPIOB
#define TOF_I2C1_SDA_Pin GPIO_PIN_9
#define TOF_I2C1_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
