/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __SYSTICK_H__
#define __SYSTICK_H__
void systick_sleep(uint32_t ms);
uint32_t systick_millis();
bool systick_has_passed(uint32_t stc, uint32_t delay_ms);
#endif //__SYSTICK_H__
