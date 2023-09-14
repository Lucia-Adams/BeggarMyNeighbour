CC = gcc

all: quality demo_shuffle

quality:  quality.o riffle.o
	cc riffle.o quality.o -o quality

quality.o : quality.c riffle.h
	cc -c quality.c

demo_shuffle : riffle.o demo_shuffle.o
	cc riffle.o demo_shuffle.o -o demo_shuffle

demo_shuffle.o : demo_shuffle.c riffle.h
	cc -c demo_shuffle.c

riffle.o : riffle.c riffle.h
	cc -c riffle.c
