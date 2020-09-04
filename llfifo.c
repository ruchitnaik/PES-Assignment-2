#include "llfifo.h"
#include <stdlib.h>
#include <stdint.h>

// A linked list (LL) node to store a queue entry 
typedef struct ll_node {
    int32_t key;
    struct ll_node* next;
} node;

typedef struct llfifo_s {
    struct ll_node *front, *rear;
    uint32_t counter;
} llfifo_t;
 
/*
 * Initializes the FIFO
 *
 * Parameters:
 *   capacity  the initial size of the fifo, in number of elements
 * 
 * Returns:
 *   A pointer to an llfifo_t, or NULL in case of an error.
 */
llfifo_t *llfifo_create(int capacity) {
    if (capacity <=0)
        return NULL;

    llfifo_t* fifo = (llfifo_t *) malloc (sizeof(node)*capacity);
    fifo->counter = capacity;
    fifo->front = fifo->rear = NULL;
    return fifo;
}

/*
 * Enqueues an element onto the FIFO, growing the FIFO by adding
 * additional elements, if necessary
 *
 * Parameters:
 *   fifo    The fifo in question
 *   element The element to enqueue
 * 
 * Returns:
 *   The new length of the FIFO on success, -1 on failure
 */
int llfifo_enqueue(llfifo_t *fifo, void *element) {

    int* ele = (int *)element;
    size_t len = 0;

    if (fifo->rear == NULL) {
        fifo->front->key = fifo->rear->key = *ele;
        fifo->front->next = fifo->rear->next = NULL;
    }

    len = llfifo_capacity(fifo);
    if(len < fifo->counter) {
        // Change to Right Logic - Incorrect Logic 
        fifo->rear->next->key = *ele;
        fifo->rear->next->next = NULL;
        fifo->rear->key = fifo->rear->next->key;
        fifo->rear->next = fifo->rear->next->next;

    }
    else {
        
    }
}



/*
 * Returns the FIFO's current capacity
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns:
 *   The current capacity, in number of elements, for the FIFO
 */
int llfifo_capacity(llfifo_t *fifo) {
    int count = 0;   
    node* current = fifo->rear;  
    while (current != NULL) { 
        count++; 
        current = current->next; 
    } 
    return count; 
}

/*
 * Teardown function. The llfifo will free all dynamically allocated
 * memory. After calling this function, the fifo should not be used
 * again!
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns:
 *   none
 */
void llfifo_destroy(llfifo_t *fifo) {
    node* head = fifo->rear;
    node* curr;
    int len = llfifo_capacity(fifo);
    while(curr->next != NULL) {
        curr = head->next;
        free(head); 
    }
    head = curr;
    if (len < fifo->counter) {
        while (fifo->counter - len == 1) {
            curr = head->next;
            free(head);
        }
    }
}
