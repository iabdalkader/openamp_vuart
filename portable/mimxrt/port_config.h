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

// DTCM
#define SHM_ORIGIN      0x20000000
#define SHM_LENGTH      64K

#define RAM_ORIGIN      0x1FFE0000
#define RAM_LENGTH      128K

#define ROM_ORIGIN      0x80000000
#define ROM_LENGTH      128K

#define LED_RED_PIN      11
#define LED_RED_PORT     GPIO10

#define LED_GREEN_PIN    12
#define LED_GREEN_PORT   GPIO10

#define LED_BLUE_PIN     13
#define LED_BLUE_PORT    GPIO10

#endif //__PORT_CONFIG_H
