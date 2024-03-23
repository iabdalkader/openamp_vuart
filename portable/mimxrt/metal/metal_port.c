/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include "fsl_common.h"
#include "fsl_mu.h"

#include "metal/sys.h"
#include "metal/utilities.h"
#include "metal/device.h"

struct metal_state _metal;

int metal_sys_init(const struct metal_init_params *params) {
    metal_unused(params);

    // Init MU.
    MU_Init(MUB);

    // Configure and enable MU IRQs.
    MU_ClearStatusFlags(MUB, kMU_GenInt0Flag);
    NVIC_SetPriority(MUB_IRQn, 1);
    NVIC_EnableIRQ(MUB_IRQn);
    MU_EnableInterrupts(MUB, kMU_GenInt0InterruptEnable);

    #if 0 //#ifndef VIRTIO_USE_DCACHE
    // If cache management is not enabled, configure the MPU to disable caching
    // for the entire shared memory region.
    ARM_MPU_Disable();
    // Normal type, not shareable, non-cacheable
    MPU->RBAR = ARM_MPU_RBAR(7, METAL_MPU_REGION_BASE);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, METAL_MPU_REGION_SIZE);
    // Enable MPU
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_HFNMIENA_Msk);
    #endif
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
    MU_TriggerInterrupts(MUB, kMU_GenInt0InterruptTrigger);
    return 0;
}

void MUB_IRQHandler(void) {
    if (MU_GetStatusFlags(MUB) & kMU_GenInt0Flag) {
        MU_ClearStatusFlags(MUB, kMU_GenInt0Flag);
        metal_rproc_notified();
    }
    __DSB();
}
