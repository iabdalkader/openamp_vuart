/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include <stdint.h>
#include <stdbool.h>
#include CMSIS_MCU_H

static volatile uint32_t ticks;

void SysTick_Handler(void) {
    ticks ++;
}

void systick_sleep(volatile uint32_t ms) {
    uint32_t curr_ticks = ticks;
    while ((ticks - curr_ticks) < ms) {
        __WFI();
    }
}

uint32_t systick_millis() {
    return ticks;
}

bool sys_tick_has_passed(uint32_t start_tick, uint32_t delay_ms) {
    return (ticks - start_tick) >= delay_ms;
}
