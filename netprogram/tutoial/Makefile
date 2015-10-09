all: server server2 client

objects = server.o server2.o client.o
CFLAGS += -g

server: server.o
	$(CC) $^ -o $@

server2: server2.o
	$(CC) $^ -o $@

client: client.o
	$(CC) $^ -o $@

$(objects):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	@rm -rf server server2 client *.o
