# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: Copyright © 2024 Intel Corporation.
#
# Makefile for jclklib client
#
# @author Christopher Hall <christopher.s.hall@intel.com>
# @copyright © 2024 Intel Corporation.
# @license BSD-3-Clause
#
###############################################################################


JCLKLIB_CLIENT_DIR := $(shell pwd)
JCLKLIB_TOPLEVEL_DIR = $(JCLKLIB_CLIENT_DIR)/..
JCLKLIB_COMMON_DIR = $(JCLKLIB_TOPLEVEL_DIR)/common
LIBPTPMGMT_PUB_DIR = $(JCLKLIB_TOPLEVEL_DIR)/../pub/
LIBS = pthread rt rtpi
LIBS_FLAGS = $(foreach lib,$(LIBS),-l$(lib))
OBJ = jclk_init msgq_tport message null_tport transport msgq_tport notification_msg connect_msg jclk_client_state subscribe_msg jclklib_client_api_c
COMMON_OBJ = print sighandler transport msgq_tport message connect_msg subscribe_msg notification_msg jclk_subscription
OBJ_FILES = $(foreach f,$(OBJ),$(f).o)
DEPENDS = $(foreach f,$(OBJ),$(f).d)
COMMON_OBJ_DIR = $(JCLKLIB_COMMON_DIR)/obj
COMMON_OBJ_FILES = $(foreach obj,$(COMMON_OBJ),$(COMMON_OBJ_DIR)/$(obj).o)
REAL_TARGETS = libjclk.so

.PHONY: default
default:
	$(MAKE) -s -C $(JCLKLIB_CLIENT_DIR) build-all 2>&1

.PHONY: build-prep
build-prep:
	echo "Running" $@
	$(MAKE) -C $(JCLKLIB_CLIENT_DIR) $(DEPENDS) 2>&1


%.d : %.cpp
	echo "[MAKEDEP]" $@
	g++ -I $(JCLKLIB_TOPLEVEL_DIR) -I $(LIBPTPMGMT_PUB_DIR) -MM -MF $@ $<

.PHONY: clean
clean:
	$(RM) -rf *.o *.d $(REAL_TARGETS)

ifneq ($(MAKECMDGOALS),)
ifeq ($(findstring build-prep,$(MAKECMDGOALS)),)
ifeq ($(findstring build-all,$(MAKECMDGOALS)),)
ifeq ($(findstring clean,$(MAKECMDGOALS)),)
ifneq ($(suffix $(MAKECMDGOALS)),.d)
-include $(DEPENDS)
endif
endif
endif
endif
endif

pathof_relative_to = $(foreach abpth,$(foreach dep,$1,$(shell realpath $(dep))), \
$(shell realpath --relative-to="$2" $(abpth)))

.PHONY: build-all
build-all: build-prep
	echo "Running" $@
	$(MAKE) -C $(JCLKLIB_CLIENT_DIR) $(REAL_TARGETS)

libjclk.so: $(OBJ_FILES) $(COMMON_OBJ_FILES)
	echo "[LINK]" $@ "{" $(call pathof_relative_to,$^,$(JCLKLIB_TOPLEVEL_DIR)) "}" | fold -s
	g++ -shared -o $@ $^ $(LIBS_FLAGS) -fdiagnostics-color=always

%.o : %.cpp
	echo "[COMPILE]" $<
	g++ -c $< -I $(JCLKLIB_TOPLEVEL_DIR) -I $(LIBPTPMGMT_PUB_DIR) -fPIC -fdiagnostics-color=always
