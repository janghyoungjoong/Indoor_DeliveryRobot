/*
 * class_3180f.c
 *
 *  Created on: May 11, 2025
 *      Author: JenogWoo
 */

#include "class_3180f.h"   // l_chan.h 헤더 파일 포함
#include "main.h"

            ///// 이찬주 교수님 연구실///// 14.00f;

void class_3180f(void) {
    // x 값을 다른 C 파일에서 사용
    if (15.50f > x) {
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

