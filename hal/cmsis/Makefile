# This file is part of the openamp_vurat example.
#
# Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
# This work is licensed under the MIT license, see the file LICENSE for details.
#
# CMSIS Makefile
SRC_S = src/$(PORT)/$(STARTUP).s
SRC_C = src/$(PORT)/$(SYSTEM).c

OBJS  = $(addprefix $(BUILD_DIR)/, $(SRC_S:.s=.o))
OBJS += $(addprefix $(BUILD_DIR)/, $(SRC_C:.c=.o))
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

$(BUILD_DIR)/%.o: %.S
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJS:%.o=%.d)
