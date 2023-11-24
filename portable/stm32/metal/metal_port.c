/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include "metal/sys.h"
#include "metal/utilities.h"
#include "metal/device.h"
#include STM32_HAL_H

struct metal_state _metal;

int metal_sys_init(const struct metal_init_params *params) {
    metal_unused(params);

    // Clear HSEM pending IRQ.
    //HSEM_COMMON->ICR |= (uint32_t)__HAL_HSEM_SEMID_TO_MASK(METAL_HSEM_ID_REMOTE);
    //HAL_NVIC_ClearPendingIRQ(HSEM2_IRQn);

    // Enable and configure HSEM.
    __HAL_RCC_HSEM_CLK_ENABLE();
    HAL_NVIC_SetPriority(HSEM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(HSEM2_IRQn);
    HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(METAL_HSEM_ID_REMOTE));

    metal_bus_register(&metal_generic_bus);
    return 0;
}

void metal_sys_assert(bool cond) {
    assert(cond);
}

void metal_sys_finish(void) {
    metal_bus_unregister(&metal_generic_bus);
}

unsigned int sys_irq_save_disable(void) {
    unsigned int state = __get_PRIMASK();
    __disable_irq();
    return state;
}

void sys_irq_restore_enable(unsigned int state) {
    __set_PRIMASK(state);
}

void sys_irq_enable(unsigned int vector) {
    metal_unused(vector);
}

void sys_irq_disable(unsigned int vector) {
    metal_unused(vector);
}

void *metal_machine_io_mem_map(void *va, metal_phys_addr_t pa,
                               size_t size, unsigned int flags) {
    metal_unused(pa);
    metal_unused(size);
    metal_unused(flags);
    return va;
}

void metal_machine_cache_flush(void *addr, unsigned int len) {
}

void metal_machine_cache_invalidate(void *addr, unsigned int len) {
}

int metal_rproc_notify(void *priv, uint32_t id) {
    HAL_HSEM_FastTake(METAL_HSEM_ID_MASTER);
    HAL_HSEM_Release(METAL_HSEM_ID_MASTER, 0);
    return 0;
}

void HSEM2_IRQHandler(void) {
    HAL_HSEM_IRQHandler();
    HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(METAL_HSEM_ID_REMOTE));
    metal_rproc_notified();
}
