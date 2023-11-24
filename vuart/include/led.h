/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __LED_H__
#define __LED_H__
typedef enum {
    LED_RED,
    LED_GREEN,
    LED_BLUE,
} led_t;

void led_init(led_t led);
void led_write(led_t led, uint32_t value);
#endif //__LED_H__
