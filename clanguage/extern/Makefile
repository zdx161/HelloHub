all: extern1.o extern2.o
	gcc extern1.o extern2.o -o all
extern1.o:extern.h
	gcc -c extern1.c
extern2.o:extern.h
	gcc -c extern2.c

.PHONY:clean
clean:
	rm -rf all *.o
