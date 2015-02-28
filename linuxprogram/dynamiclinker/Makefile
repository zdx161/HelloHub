################################################
#
# the project manager file
# Makefile for make tool
#
################################################

all: first second example

EXEFILES = first second example
DFLAGS = -DUSE_SECOND_WAY

first:main.c libsimplemath.so
	gcc -rdynamic -o $@ main.c -ldl
second:main.c libsimplemath.so
	gcc -L $$(pwd) $(DFLAGS) -o $@ main.c -lsimplemath

libsimplemath.so:simplemath.o
	gcc -shared -o $@ $< 
	@export LD_LIBRARY_PATH=$$(pwd); \
	echo $$LD_LIBRARY_PATH

simplemath.o:simplemath.c
	gcc -fpic -c $<

example:man_example.o
	gcc -rdynamic -o example man_example.o -ldl

man_example.o: man_example.c
	gcc -c $<

.PHONY:clean

clean:
	@rm -rf $(EXEFILES) *.o *.so
