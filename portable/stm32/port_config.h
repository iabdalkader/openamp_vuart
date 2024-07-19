/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __PORT_CONFIG_H
#define __PORT_CONFIG_H

#ifndef RAM_IMAGE
#define RAM_IMAGE       (1)
#endif

#define SHM_ORIGIN      0x38000000
#define SHM_LENGTH      64K

#define RAM_ORIGIN      0x30000000
#define RAM_LENGTH      128K

// Note when booting from SDRAM use SDRAM bank1 address at 0x70000000
// or 0x60000000 (if banks are swapped) but Never use 0xC0000000, as
// by default it's set as Never Execute.
// #define RAM_ORIGIN      0x70380000
// #define RAM_LENGTH      512K
// #define RAM_MPU_REGION  MPU_REGION_SIZE_512KB

#define ROM_ORIGIN      0x081E0000
#define ROM_LENGTH      128K

#endif //__PORT_CONFIG_H
