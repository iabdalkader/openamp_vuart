# This file is part of the openamp_vurat example.
#
# Copyright (c) 2024 Ibrahim Abdelkader <iabdalkader@openmv.io>
# This work is licensed under the MIT license, see the file LICENSE for details.
#
# MIMXRT Makefile
SRCS = $(addprefix drivers/,\
	fsl_mu.c\
	fsl_pmu.c\
	fsl_clock.c\
	fsl_common_arm.c\
	fsl_anatop_ai.c\
	fsl_dcdc.c\
	fsl_gpio.c\
	cm4/fsl_cache.c\
)

OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
OBJ_DIRS = $(sort $(dir $(OBJS)))

all: | $(OBJ_DIRS) $(OBJS)
$(OBJ_DIRS):
	$(MKDIR) -p $@

$(BUILD_DIR)/%.o : %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o : %.s
	$(ECHO) "AS $<"
	$(AS) $(AFLAGS) $< -o $@

-include $(OBJS:%.o=%.d)
