CC = gcc

all: single byn

single: beggar.o shuffle.o queue.o single.o
	gcc -o single single.o shuffle.o queue.o beggar.o -lgsl -lgslcblas -lm

byn: beggar.o shuffle.o queue.o byn.o
	gcc -o byn byn.o shuffle.o queue.o beggar.o -lgsl -lgslcblas -lm
