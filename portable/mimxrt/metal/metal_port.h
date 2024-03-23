/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __MIMXRT_METAL_PORT_H__
#define __MIMXRT_METAL_PORT_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define METAL_HAVE_STDATOMIC_H      0
#define METAL_HAVE_FUTEX_H          0

#define METAL_PROCESSOR_CPU_H       "metal/processor/arm/cpu.h"
#define METAL_PROCESSOR_ATOMIC_H    "metal/processor/arm/atomic.h"
#define METAL_MAX_DEVICE_REGIONS    2

// Note set to 1 to enable log output.
#define METAL_LOG_HANDLER_ENABLE    1

#define metal_cpu_yield()

// Shared memory config
#define METAL_SHM_NAME              "OPENAMP_SHM"
// Note 1K must be reserved at the start of the openamp
// shared memory region, for the shared resource table.
#define METAL_RSC_ADDR              ((void *) _openamp_shm_region_start)
#define METAL_RSC_SIZE              (1024)

#define METAL_SHM_ADDR              ((metal_phys_addr_t) (_openamp_shm_region_start + METAL_RSC_SIZE))
#define METAL_SHM_SIZE              ((size_t) (_openamp_shm_region_end - _openamp_shm_region_start - METAL_RSC_SIZE))

#define METAL_MPU_REGION_BASE       ((uint32_t)_openamp_shm_region_start)
#define METAL_MPU_REGION_SIZE       (ARM_MPU_REGION_SIZE_64KB)

extern const char _openamp_shm_region_start[];
extern const char _openamp_shm_region_end[];

void metal_sys_assert(bool cond);
int metal_rproc_notify(void *priv, uint32_t id);
extern void metal_rproc_notified();

#endif // __MIMXRT_METAL_PORT_H__
