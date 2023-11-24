/*
 * Copyright (c) 2015, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	config.h
 * @brief	Generated configuration settings for libmetal.
 */

#ifndef __METAL_CONFIG__H__
#define __METAL_CONFIG__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "metal/metal_port.h"

/** Library major version number. */
#define METAL_VER_MAJOR     1

/** Library minor version number. */
#define METAL_VER_MINOR     5

/** Library patch level. */
#define METAL_VER_PATCH     0

/** Library version string. */
#define METAL_VER           "1.5.0"

#ifndef METAL_PROCESSOR_CPU_H
#define METAL_PROCESSOR_CPU_H    "metal/processor/arm/cpu.h"
#endif 

#ifndef METAL_PROCESSOR_ATOMIC_H
#define METAL_PROCESSOR_ATOMIC_H    "metal/processor/arm/atomic.h"
#endif 

#define HAVE_STDATOMIC_H    METAL_HAVE_STDATOMIC_H
#define HAVE_FUTEX_H        METAL_HAVE_FUTEX_H

#ifdef __cplusplus
}
#endif

#endif /* __METAL_CONFIG__H__ */
