#* ******************************************************************************
#* Copyright (C) 2022 Sky group of companies, All Rights Reserved
#* * --------------------------------------------------------------------------
#* * THIS SOFTWARE CONTRIBUTION IS PROVIDED ON BEHALF OF SKY PLC. 
#* * BY THE CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
#* * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#* * A PARTICULAR PURPOSE ARE DISCLAIMED
#* ******************************************************************************
#*
#*   ** Project      : cunit_hal_test
#*   ** @addtogroup  : cunit_hal_test
#*   ** @file        : makefile
#*   ** @author      : gerald.weatherup@sky.uk
#*   ** @date        : 20/05/2022
#*   **
#*   ** @brief : Makefile for hal_test
#*   ** 
#*
#* ******************************************************************************
TARGET_EXEC ?= wifi_hal_stub

$(info Module [$(TARGET_EXEC)])

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
export PATH := $(shell pwd)/toolchain:$(PATH)
BUILD_DIR := $(ROOT_DIR)/obj
BIN_DIR := $(ROOT_DIR)/bin

SRC_DIRS = $(ROOT_DIR)/src
INC_DIRS := $(ROOT_DIR)/../include

MKDIR_P ?= @mkdir -p

$(info SRC_DIRS: $(SRC_DIRS))

ccred=$(echo -e "\033[0;31m")
ccyellow=$(echo -e "\033[0;33m")
ccend=$(echo -e "\033[0m")

ifeq ($(TARGET),)
$(info TARGET NOT SET )
$(info TARGET FORCED TO Linux)
TARGET=linux
endif

$(info TARGET [$(TARGET)])

ifeq ($(TARGET),arm)
CUNIT_VARIANT=arm-rdk-linux-gnueabi
CC ?= arm-rdk-linux-gnueabi-gcc --hello -mthumb -mfpu=vfp -mcpu=cortex-a9 -mfloat-abi=soft -mabi=aapcs-linux -mno-thumb-interwork -ffixed-r8 -fomit-frame-pointer 
#CC += --sysroot=/home/gew04/SDK/rdk/2.0/sysroots/cortexa9t2-vfp-rdk-linux-gnueabi
CFLAGS += -Wall -ggdb
CFLAGS += --sysroot=${ROOT_DIR}/sysroot
CFLAGS += -D__arm__
INC_DIRS += $(ROOT_DIR)/sysroot/usr/include
LDFLAGS += -libhal_wifi.a
HAL_LIB_DIR := $(ROOT_DIR)/libs
LDFLAGS = -Wl,-rpath,$(HAL_LIB_DIR) -L$(HAL_LIB_DIR) -lhal_wifi

endif

ifeq ($(TARGET),linux)
CUNIT_VARIANT=i686-pc-linux-gnu
INC_DIRS += $(ROOT_DIR)/linux/cunit/include
#CFLAGS += -fsanitize=address -fbounds-check
#LDFLAGS += -lasan
CC:=gcc -ggdb -o0 -Wall
SRC_DIRS += $(ROOT_DIR)/src
endif

CUNIT_LIB_DIR = $(ROOT_DIR)/cunit/$(CUNIT_VARIANT)/lib
#LIB_DIR = $(CUNIT_LIB_DIR)
LIB_DIR = ""
INC_DIRS += $(ROOT_DIR)/cunit/$(CUNIT_VARIANT)/include/CUnit

LDFLAGS += -Wl,-rpath,$(LIB_DIR) -L$(LIB_DIR) -lcunit

CFLAGS += -DTEST -DWIFI_HAL_VERSION_3 -DWIFI_HAL_VERSION_3_PHASE2 #-DUNITY_EXCLUDE_SETJMP_H -DUNITY_OUTPUT_COLOR -DUNITY_INCLUDE_PRINT_FORMATTED
CFLAGS += -DCONFIG_WIFI_HAL_NUMBER_OF_RADIOS
#CFLAGS += -DSKY -DWIFI_HAL_VERSION_3 -DSKY_LED_AND_GPIO -DCONFIG_SKY_ETHAN -DWL_DEFAULT_NUM_SSID=16 -DBRCM_DEFAULT_NUM_MBSS=16 -DAX_SUPPORT -DBUILD_RDKWIFI -D_SR300_PRODUCT_REQ_

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(subst $(ROOT_DIR),$(BUILD_DIR), $(SRCS:.c=.o))

#$(info ------------ )
#$(info SRCS: $(SRCS))
#$(info ------------ )
#$(info OBJS: $(OBJS))
#$(info ------------ )

INC_DIRS += $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

#$(info ------------ )
#$(info INC_FLAGS: $(INC_FLAGS))
#$(info ------------ )

# Library Path

# Final conversions
DEPS := $(OBJS:.o=.d)
#vpath %.c $(SRC_DIRS)
XCFLAGS := $(CFLAGS) $(INC_FLAGS) 

test: $(TEST_OBJS) $(OBJS)
	@echo Linking $@ $(BUILD_DIR)/$(TARGET_EXEC)
	@$(CC) $(OBJS) -o $(BUILD_DIR)/$(TARGET_EXEC) $(LDFLAGS)
	@cp $(BUILD_DIR)/$(TARGET_EXEC) $(BIN_DIR)

#@echo Copying CUNIT: [$(CUNIT_LIB_DIR)/*.so*] to [$(BIN_DIR)]
#@rsync -qzav $(CUNIT_LIB_DIR)/*.so* $(BIN_DIR)

# c source
$(BUILD_DIR)/%.o: %.c 
	$(MKDIR_P) $(dir $@)
	@echo Building $<
	@$(CC) $(XCFLAGS) -c $< -o $@

.PHONY: clean list arm linux

arm:
	make TARGET=arm

linux:
	make TARGET=arm

clean:
	@echo Performing Clean
	@$(RM) -rf $(BUILD_DIR)
	@echo Clean Completed

list:
	@echo 
	@echo CC:$(COMPILER)
	@echo 
	@echo OBJS:$(OBJS)
	@echo 
	@echo SRC:$(SRCS)
	@echo
	@echo
	@echo CFLAGS:$(CFLAGS)
	@echo
	@echo LDFLAGS:$(LDFLAGS)
	@echo 
	@echo SRC_DIRS:$(SRC_DIRS)
	@echo 
	@echo INC_DIRS:$(INC_DIRS)
	@echo 
	@echo INC_FLAGS:$(INC_FLAGS)
	@echo 
	@echo TEST_OBJS:$(TEST_OBJS)

-include $(DEPS)
