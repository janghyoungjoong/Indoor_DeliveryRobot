#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "can.h"
#include "ultrasonic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tof.h"
#include "VL53L1X_api.h"

// 목적지 함수 헤더
#include "motor_stop.h"
#include "L_chan.h"
#include "K_hun.h"
#include "J_yoo.h"
#include "L_rok.h"
#include "class_3140f.h"
#include "class_3170f.h"
#include "class_3180f.h"

extern uint16_t TOF_ReadDistance(void);

#define TOF_ADDR 0x52  // 기본 주소 (0x29 << 1)
#define TOF1_PORT GPIOA
#define TOF1_PIN  GPIO_PIN_5
#define TOF2_PORT GPIOA
#define TOF2_PIN  GPIO_PIN_7

void class_3170f(void){

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);

	while (1) {

		TOF_Start(TOF1_PORT, TOF1_PIN);

		uint16_t d = TOF_ReadDistance();  // mm 단위

		send_trigger_pulse();  // 초음파 트리거
		HAL_Delay(10);
		float dist_L = get_distance_L();
		float dist_R = get_distance_R();

		char msg[128];
		snprintf(msg, sizeof(msg),
				" TOF1: %d mm \r\n US_L: %.2f cm | US_R: %.2f cm \r\n CAN X: %.3f Y: %.3f \r\n ----------------------------\r\n",
				d, dist_L, dist_R, x, y);
		HAL_UART_Transmit(&huart2, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart3, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);
		HAL_Delay(300);  // 출력 속도 조절

		if (x < 14.00f) {
			// 거리 기반 속도 조절
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 9000);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 8300);

			if (d < 400) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 9000);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 8300);
			} else if (d < 600) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 8400);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 8300);
			} else if (d < 800) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 7700);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 8300);
			} else if (d < 1000) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 7000);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 8300);
			} else if (d < 1200) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 7000);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 8900);
			} else if (d < 1400) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 7000);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 9500);
			} else if (d < 1600) {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 7000);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 10000);
			} else {
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 5000);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 10000);
			}
		} else {

			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);

			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 10000);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 10000);
			HAL_Delay(6000);

			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0);

			HAL_Delay(1000);
			if (x != 0) {
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);

				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 9000);
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 8300);
			}
		}
	}
}
