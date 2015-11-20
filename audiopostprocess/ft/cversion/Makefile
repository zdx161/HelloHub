all: test

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, object/%.o, $(SRC))

CPPFLAGS =
CFLAGS = -g
LDFLAGS = -lm

test:$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ):object/%.o:%.c
	$(shell if [ ! -d ./object ]; then mkdir object; fi)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:all clean ts
clean:
	@rm -rf test object

ts:
	@echo $(OBJ)
