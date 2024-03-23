/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include <stdint.h>
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "fsl_cache.h"
#include "clock_config.h"

int port_init(void) {
    L1CACHE_DisableSystemCache();
    BOARD_BootClockRUN();

    //SystemCoreClockUpdate();
    SystemCoreClock = CLOCK_GetRootClockFreq(kCLOCK_Root_M4);
    SysTick_Config(SystemCoreClock / 1000U);

    CLOCK_EnableClock(kCLOCK_Iomuxc);
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_02_GPIO10_IO11, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_03_GPIO10_IO12, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_04_GPIO10_IO13, 0U);
    return 0;
}
