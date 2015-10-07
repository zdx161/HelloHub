#####################################################################
#                      Makefile
#                     2015-09-02
#####################################################################

all:libbacktrace.so test

SRC_FILES := gcc-demangle/cp-demangle.c
INCLUDE_FILES := \
	include \
	libcorkscrew/ \
	libcorkscrew/arch-x86 \
	gcci-demangle

SRC_FILES += \
	libcorkscrew/backtrace.c \
	libcorkscrew/backtrace-helper.c \
	libcorkscrew/demangle.c \
	libcorkscrew/map_info.c \
	libcorkscrew/ptrace.c \
	libcorkscrew/symbol_table.c \
	libcorkscrew/arch-x86/backtrace-x86.c \
	libcorkscrew/arch-x86/ptrace-x86.c

DFLAGS += -DHAVE_STRING_H -DHAVE_STDLIB_H -DIN_GLIBCPP_V3 -D_GNU_SOURCE
CFLAGS += -shared -fpic -rdynamic -g -std=gnu99 -m32
LFLAGS += -ldl -lpthread
IFLAGS += $(patsubst %, -I%, $(INCLUDE_FILES))

objects = $(patsubst %.c, %.o, $(SRC_FILES))

libbacktrace.so:$(objects)
	gcc $(IFLAGS) $(DFLAGS) $(CFLAGS)  $+ -o $@ $(LFLAGS)

$(objects):%.o:%.c
	gcc $(DFLAGS) $(IFLAGS) -g -std=gnu99 -m32 -c $< -o $@

test:test.o
	gcc -rdynamic -g -std=gnu99 -m32 -L$(shell pwd) $< -o $@ -ldl -lbacktrace
test.o:test.cpp
	gcc -Iinclude -g -std=gnu99 -m32 -c $< -o $@

.PHONY: clean all
clean:
	-rm -rf $(objects) libbacktrace.so test test.o

#g++ -I. -Iinclude -L$(pwd) -rdynamic -g -m32 -o testmy testmy.cpp -ldl -lutils
#gcc -g -I. -Iinclude -rdynamic -shared -fpic -L$(pwd) -o libutils.so CallStack.cpp -std=gnu99 -m32 -ldl -lpthread -lbacktrace
#g++ -I. -Iinclude -fpic -shared -rdynamic -g -o libtestbtforc.so testmyforc.cpp -ldl -m32
