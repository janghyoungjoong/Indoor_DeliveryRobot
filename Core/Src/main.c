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

void delay_us(uint16_t us); // 초음파 딜레이
void send_trigger_pulse(void); // 초음파 TRIG 설정


#define TOF_ADDR 0x52  // 기본 주소 (0x29 << 1)
#define TOF1_PORT GPIOA
#define TOF1_PIN  GPIO_PIN_5
#define TOF2_PORT GPIOA
#define TOF2_PIN  GPIO_PIN_7

// 전역 변수
uint8_t bt_data_received = 0;
extern uint8_t bt_rx_data;

volatile uint8_t tof_mode = 0;

void TOF_Enable(GPIO_TypeDef *port, uint16_t pin); // 센서 초기화
void TOF_Disable(GPIO_TypeDef *port, uint16_t pin); //센서 초기화
void TOF_Start(GPIO_TypeDef *port, uint16_t pin); // 센서 시작

uint16_t TOF_ReadDistance(void);

extern uint8_t bt_rx_buffer[100];

// CAN 수신 콜백 함수 프로토타입
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

// Bluetooth 수신 콜백 함수 프로토타입
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void SystemClock_Config(void);
void Error_Handler(void);

int main(void) {
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_TIM3_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	MX_CAN_Init();
	MX_TIM2_Init();
	MX_I2C1_Init();

	CAN_filter();

	TOF_Disable(GPIOA, GPIO_PIN_5);
	TOF_Disable(GPIOA, GPIO_PIN_7);

	HAL_TIM_Base_Start(&htim3);

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0);

	// CAN 통신 시작 및 알림 활성화
	HAL_CAN_Start(&hcan);
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	// Bluetooth 수신 인터럽트 시작
	HAL_UART_Receive_IT(&huart3, &bt_rx_data, 1);

	char msg[128];
	char mmg[128];

	while (1) {
		send_trigger_pulse();
		HAL_Delay(100);
		// CAN 데이터 수신 처리


		// Bluetooth 데이터 수신 처리 (명령 실행)
		if (bt_data_received) {
			int cmd = atoi((char*) bt_rx_buffer);
			switch (cmd) {
			case 1:
				l_chan();
				break;
			case 2:
				k_hun();
				break;
			case 3:
				j_yoo();
				break;
			case 4:
				l_rok();
				break;
			case 5:
				class_3140f();
				break;
			case 6:
				class_3170f();
				break;
			case 7:
				class_3180f();
				break;
			default:
				motor_stop();
				break;
			}
			bt_data_received = 0;
		}

		HAL_Delay(100);
	}
}

// CAN 수신 콜백 함수

// Bluetooth 수신 콜백 함수 (bluetooth.c에서 구현 가능)
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

void Error_Handler(void) {
	__disable_irq();
	while (1) {
	}
}
