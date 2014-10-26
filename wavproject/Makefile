wav:main.o option.o pcm.o wav.o common.o
	gcc main.o option.o pcm.o wav.o common.o -o wav -lm
main.o: main.c
	gcc -g -c main.c
option.o:
	gcc -g -c option.c
pcm.o:pcm.c
	gcc -g -c pcm.c
wav.o:wav.c
	gcc -g -c wav.c
common.o:common.c
	gcc -g -c common.c

.PHONY: clean all
clean:
	-rm -f wav *.o
