
src = $(wildcard *.c)
object = $(patsubst %.c, %.o, $(src))
bin = $(patsubst %.o, %, $(object))

CFLAGS = -g
#LDFLAGS = -lm

all: $(bin)

%:%.o
	$(CC) -o $@ $^ #$(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@



.PHONY: clean test

clean:
	@rm -rf $(object) $(bin)

test:
	@echo $(bin)
