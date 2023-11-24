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
#include "systick.h"
#include "vuart.h"

#include "openamp.h"
#include "common.h"

void fatal_error(const char *msg) {
    led_init(LED_RED);
    while (1) {
        led_write(LED_RED, 0);
        systick_sleep(250);
        led_write(LED_RED, 1);
        systick_sleep(250);
    }
}

void vuart_callback(vuart_t *vuart) {
    // Data was received, and stored in the ring buffer.
    // Add code to process the message if needed.
}

int main(void) {
    static vuart_t vuart;

    // Port-specific init code.
    port_init();

    // Initialize OpenAMP.
    openamp_init();

    // Create Virtual UART device
    // defined by a rpmsg channel attached to the remote device
    if (vuart_init(&vuart, vuart_callback, NULL) != 0) {
        fatal_error("vuart_init failed\n");
    }

    led_init(LED_BLUE);
    while (1) {
        if (vuart_any(&vuart)) {
            uint8_t rxbuf[4096];
            size_t bytes = vuart_read(&vuart, rxbuf, sizeof(rxbuf));
            vuart_write(&vuart, rxbuf, bytes);
        }
        led_write(LED_BLUE, 0);
        systick_sleep(500);
        led_write(LED_BLUE, 1);
        systick_sleep(500);
    }
}
