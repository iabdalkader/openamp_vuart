/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include <stdint.h>
#include <stdbool.h>
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "led.h"
#include "port_config.h"

void led_init(led_t led) {
    uint32_t pin;
    GPIO_Type *port;

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

    gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 0 };
    GPIO_PinInit(port, pin, &led_config);
}

void led_write(led_t led, uint32_t value) {
    uint32_t pin;
    GPIO_Type *port;

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

    GPIO_PinWrite(port, pin, value);
}
