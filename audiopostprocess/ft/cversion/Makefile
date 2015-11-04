all: test


CPPFLAGS =
CFLAGS = -g
LDFLAGS =

test:main.o utils.o
	$(CC) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@





.PHONY:all clean

clean:
	@rm -rf test *.o
