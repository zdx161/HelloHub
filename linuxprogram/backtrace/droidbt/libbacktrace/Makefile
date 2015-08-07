#
# Copyright (C) 2014 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


common_cflags := \
	-Wall \
	-Werror \

common_conlyflags := \
	-std=gnu99 \

common_cppflags := \
	-std=gnu++11 \

build_host := false
ifeq ($(HOST_OS),linux)
ifeq ($(HOST_ARCH),$(filter $(HOST_ARCH),x86 x86_64))
build_host := true
endif
endif


#-------------------------------------------------------------------------
# The libbacktrace library.
#-------------------------------------------------------------------------
libbacktrace_src_files := \
	BacktraceImpl.cpp \
	BacktraceMap.cpp \
	BacktraceThread.cpp \
	thread_utils.c \

libbacktrace_shared_libraries_target := \
	libcutils \
	libgccdemangle \

libbacktrace_src_files += \
	UnwindCurrent.cpp \
	UnwindMap.cpp \
	UnwindPtrace.cpp \

libbacktrace_c_includes := \
	external/libunwind/include \

libbacktrace_shared_libraries := \
	libunwind \
	libunwind-ptrace \

libbacktrace_shared_libraries_host := \
	liblog \

libbacktrace_static_libraries_host := \
	libcutils \

libbacktrace_ldlibs_host := \
	-lpthread \
	-lrt \

module := libbacktrace
module_tag := optional
build_type := target
build_target := SHARED_LIBRARY
include $(LOCAL_PATH)/Android.build.mk
build_type := host
include $(LOCAL_PATH)/Android.build.mk
