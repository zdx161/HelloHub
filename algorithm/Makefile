vpath %.c ./ADT
vpath %.c ./tree

src = $(wildcard tree/*.c)
src += $(wildcard *.c)
bin = $(patsubst %.c, %, $(src))
object = $(patsubst %.c, %.o, $(src))

all:$(bin)

CFLAGS = -g
LDFLAGS = -lm

#use static pattern rules to build multiple execute files
$(bin):%:%.o
	$(CC) $< -o $@ $(LDFLAGS)

#failed:no patterns
#$(bin):$(object)
#	$(CC) $< -o $@    (X)
#	$(CC) $^ -o $@    (X)

#use static pattern rules to build multiple object files
$(object):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:test clean
test:
	@echo $(src)
	@echo $(bin)
	@echo $(object)

clean:
	@rm -rf $(bin) $(object)
