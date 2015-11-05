all: test


CPPFLAGS =
CFLAGS = -g
LDFLAGS = -lm

test:main.o utils.o
	$(CC) $^ -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@





.PHONY:all clean

clean:
	@rm -rf test *.o
