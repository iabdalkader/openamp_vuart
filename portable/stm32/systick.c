/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include <stdint.h>
#include <stdbool.h>
#include STM32_HAL_H

void SysTick_Handler(void) {
    HAL_IncTick();
}

void systick_sleep(volatile uint32_t ms) {
    volatile uint32_t curr_ticks = HAL_GetTick();
    while ((HAL_GetTick() - curr_ticks) < ms) {
        __WFI();
    }
}

uint32_t systick_millis() {
    return HAL_GetTick();
}

bool sys_tick_has_passed(uint32_t start_tick, uint32_t delay_ms) {
    return HAL_GetTick() - start_tick >= delay_ms;
}
