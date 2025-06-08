/*
 * j_yoo.c
 *
 *  Created on: May 11, 2025
 *      Author: JenogWoo
 */

#include "J_yoo.h"
#include "main.h"

               ///// 전유찬 교수님 연구실///// 23.00f;

void j_yoo(void) {
    // x 값을 다른 C 파일에서 사용
    if (-23.00f > x) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1);
    } else {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, 0);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0);
    }
}
