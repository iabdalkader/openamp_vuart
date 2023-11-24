/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include STM32_HAL_H
#include "led.h"

#define LED_RED_PIN      GPIO_PIN_12
#define LED_RED_PORT     GPIOI
#define LED_RED_CLK_ENABLE  __GPIOI_CLK_ENABLE

#define LED_GREEN_PIN    GPIO_PIN_13
#define LED_GREEN_PORT   GPIOJ
#define LED_GREEN_CLK_ENABLE  __GPIOJ_CLK_ENABLE

#define LED_BLUE_PIN     GPIO_PIN_3
#define LED_BLUE_PORT    GPIOE
#define LED_BLUE_CLK_ENABLE  __GPIOE_CLK_ENABLE

void led_init(led_t led) {
    uint16_t pin;
    GPIO_TypeDef *port;

    switch (led) {
        case LED_RED:
            pin = LED_RED_PIN;
            port = LED_RED_PORT;
            LED_RED_CLK_ENABLE();
            break;
        case LED_GREEN:
            pin = LED_GREEN_PIN;
            port = LED_GREEN_PORT;
            LED_GREEN_CLK_ENABLE();
            break;
        default:
        case LED_BLUE:
            pin = LED_BLUE_PIN;
            port = LED_BLUE_PORT;
            LED_BLUE_CLK_ENABLE();
            break;
    }

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pin;
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStructure);
}

void led_write(led_t led, uint32_t value) {
    uint16_t pin;
    GPIO_TypeDef *port;

    switch (led) {
        case LED_RED:
            pin = LED_RED_PIN;
            port = LED_RED_PORT;
            break;
        case LED_GREEN:
            pin = LED_GREEN_PIN;
            port = LED_GREEN_PORT;
            break;
        default:
        case LED_BLUE:
            pin = LED_BLUE_PIN;
            port = LED_BLUE_PORT;
            break;
    }

    HAL_GPIO_WritePin(port, pin, value);
}
