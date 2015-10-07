
SRC_FILES := gcc-demangle/cp-demangle.c
INCLUDE_FILES := \
	include \
	libcorkscrew/ \
	libcorkscrew/arch-x86 \
	gcci-demangle

SRC_FILES +=  \
	libcorkscrew/backtrace.c \
	libcorkscrew/backtrace-helper.c \
	libcorkscrew/demangle.c \
	libcorkscrew/map_info.c \
	libcorkscrew/ptrace.c \
	libcorkscrew/symbol_table.c \
	libcorkscrew/arch-x86/backtrace-x86.c \
	libcorkscrew/arch-x86/ptrace-x86.c

CFLAGS += -DHAVE_STRING_H -DHAVE_STDLIB_H -DIN_GLIBCPP_V3 -std=gnu99 -m32


test:
