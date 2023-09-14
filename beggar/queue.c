#include "queue.h"

/* Creates new queue node
 *
 * Params:
 * 	int val - value of new node
 * Returns:
 * 	QUEUE *node - new node pointer
 */
QUEUE *newNode(int val){
        /*pointer to a node */
        QUEUE *node;

        /* malloc room for a new node */
        if (!(node = (QUEUE *)malloc(sizeof(QUEUE)))){
                printf("Memory allocation error");
                exit(-1);
        }

        node -> value = val;
        node -> nextNode = NULL;

        return node;
}

/* Enqueues new value to queue (at end)
 *
 * Params:
 * 	int val - value to enqueue
 * 	QUEUE **start - address of pointer to queue to add to
 */
void enqueue(int val, QUEUE **start){
        /* creates a new node */
        QUEUE *nNode = newNode(val);

	/* if empty queue initialise it*/
        if (*start ==NULL){
                *start = nNode;
                return;
        }

	/* loop through to end of queue */
        QUEUE *current = *start;
        while (current->nextNode != NULL){
                current = current->nextNode;
        }
        /* now currents nextNode is NULL so thats the end of the queue*/
        current->nextNode = nNode;

}

/* Dequeues front element from given queue
 *
 * Params:
 * 	QUEUE **start - address of pointer to queue we want to dequeue from
 * Returns:
 * 	int val - value of dequeued node
 */
int dequeue(QUEUE **start){

        /* keep pointer to this so we can free it */
        QUEUE *oldStart = *start;
        /* check not trying to dequeue from nothing - return 0 if nothing as not a value */
        if (oldStart == NULL){return 0;}

        int val = oldStart->value;
        /*need to change *start hence why we have double pointer */
        *start = oldStart->nextNode;
        free(oldStart);
        return val;
}

/* Prints given queue out in a line 
 *
 * Params:
 * 	QUEUE *start - pointer of queue to print
 */
void print_queue(QUEUE *start){
        /* print the queue recursively until null node */
        if (start == NULL){
                printf("\n");
                return;
        }else{
                printf("%d ", start->value);
                print_queue(start->nextNode);
        }
}

/* Empties queue to ensure we free memory after use
 *
 * Params:
 * 	QUEUE **start - address of pointer of queue to empty
 */
void empty_queue(QUEUE **start){
        /* ensure empty to free all the mallocs for the nodes */
        if (*start == NULL){
                return;
        } else {
                dequeue(start);
                empty_queue(start);
        }
}

