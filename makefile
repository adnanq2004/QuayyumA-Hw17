all: writing.o control.o
	gcc -o writing writing.o
	gcc -o control control.o

control.o: control.h control.c
	gcc -c control.c

writing.o: writing.h writing.c
	gcc -c writing.c
