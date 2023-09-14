#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void riffle_once(void *L, int len, int size, void *work);
void riffle(void *L, int len, int size, int N);
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *));
int cmp_int(void *, void *);
int cmp_str(void *, void *);
int check_existence(void *, void *, int len, int size, int (*cmp)(void *, void *));
float quality(int *numbers, int len);
float average_quality(int N, int shuffles, int trials);
