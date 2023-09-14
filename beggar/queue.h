#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdio.h>

struct queueStruct{

        int value;
        struct queueStruct *nextNode;

};

typedef struct queueStruct QUEUE;

QUEUE *newNode(int);
void enqueue(int val, QUEUE **start);
void print_queue(QUEUE *start);
int dequeue(QUEUE **start);
void empty_queue(QUEUE **start);

#endif
