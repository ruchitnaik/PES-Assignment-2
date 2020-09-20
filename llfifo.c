/******************************************************************************
*​​Copyright​​ (C) ​​2020 ​​by ​​Arpit Savarkar
*​​Redistribution,​​ modification ​​or ​​use ​​of ​​this ​​software ​​in​​source​ ​or ​​binary
*​​forms​​ is​​ permitted​​ as​​ long​​ as​​ the​​ files​​ maintain​​ this​​ copyright.​​ Users​​ are
*​​permitted​​ to ​​modify ​​this ​​and ​​use ​​it ​​to ​​learn ​​about ​​the ​​field​​ of ​​embedded
*​​software. ​​Arpit Savarkar ​​and​ ​the ​​University ​​of ​​Colorado ​​are ​​not​ ​liable ​​for
*​​any ​​misuse ​​of ​​this ​​material.
*
******************************************************************************/ 
/**
 * @file llfifo.c
 * @brief An abstraction to maintain and instantiate Linked List Based 
 * Queue (FIFO) 
 * 
 * This file provides functions and abstractions for handling and
 * manipulating Circular Buffer
 * 
 * @author Arpit Savarkar
 * @date September 10 2020
 * @version 2.0
 * 
  Sources of Reference :
  Online Links : https://github.com/geekfactory/FIFO/blob/master/FIFO.h
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers 
  I would like to thank the SA's of the course Rakesh Kumar, Saket Penurkar and Professor Howdy Pierece for their 
  support to debug the Linkedlist FIFO Implementation. 

  This is the version 2 of the of the Code, which consists of keeping track of 2 linkedlists 
  Based on the comments/code of (Howdy Pierce, howdy.pierce@colorado.edu)
*/

#include "llfifo.h"

// Node Struct which keeps track of 
// next and key(void*)
typedef struct node_s {
    struct node_s *next;
    void* key;
}node_t;


// Defining Struct Space 
struct llfifo_s {
    int capacity;
    int length;
    node_t *head, *tail, *unused;
    int allocatednodes;
};

/*
 * Dynamically creates a new done and stores the 
 * Address of the pointer to a new node
 */
static node_t* newNode( node_t* next) {
    node_t* ne = (node_t*)malloc(sizeof(node_t));

    if(ne == NULL)
        return NULL;

    ne->next = next;
    ne->key = NULL;
    return ne;
}


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
    if(capacity < 0)
        return NULL;

    // Creates array 
    assert(capacity >= 0);
    llfifo_t* fifo = (llfifo_t*)malloc(sizeof(llfifo_t));
    assert(fifo);

    fifo->capacity = capacity;
    fifo->allocatednodes = capacity;
    fifo->length = 0;
    fifo->head = fifo->tail = fifo->unused = NULL;

    // Sends the existing location of unused to store
    // as Next to a temp variable basically 
    // Creating a linked list with a temp node pointing 
    // to unused and head of the linkedlist as fifo->unused
    for(int i =0; i<capacity; i++) {
        fifo->unused = newNode(fifo->unused);

        // Checks for Failure Case
        if(fifo->unused == NULL)
            return NULL;
    }
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

    assert(fifo);

    // ele would not point at the 2nd node of the unused 
    // linkedlist and data currently is NULL
    node_t * ele = fifo->unused;

    if(ele) {
        // Basically Dequeue and rePointer
        fifo->unused = ele->next;
    } else {
        // Increasing Capacity
        ele = newNode(fifo->head);
        if(ele == NULL)
            return -1;
        fifo->capacity++;
    }

    // Store Contents 
    ele->next = NULL;
    ele->key = element;

    // Incrementing Tail
    if(fifo->tail)
        fifo->tail->next = ele;
    
    fifo->tail = ele;
    
    // If its the first element the head is set to point to it
    if(!fifo->head)
        fifo->head = ele;
    
    return (++fifo->length);
}


/*
 * Removes ("dequeues") an element from the FIFO, and returns it
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns:
 *   The dequeued element, or NULL if the FIFO was empty
 */
void *llfifo_dequeue(llfifo_t *fifo) {
    
    assert(fifo);
    node_t* ele = fifo->head;
    if(ele == NULL)
        return NULL;
    
    // Move Head 1 node upwards
    fifo->head = ele->next;
    // Set this next to point to fifo->unused
    ele->next = fifo->unused;

    // Is empty 
    if(fifo->head == NULL)
        fifo->tail = NULL;
    
    fifo->unused = ele;
    fifo->length--;
    return ele->key;
}


/*
 * Returns the number of elements currently on the FIFO. 
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns:
 *   The number of elements currently on the FIFO
 */
int llfifo_length(llfifo_t *fifo) {
    assert(fifo);
    return fifo->length;
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
    assert(fifo);
    return (fifo->capacity);
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

    assert(fifo);
    node_t* ele;
    int num_freed =0;

    // To Free the Dynamically allocated list  
    while( (ele = fifo->head) ) {
        fifo->head = ele->next;
        free(ele);
        num_freed++;
    }

    // To Be the Unused list 
    while( (ele = fifo->unused) ) {
        fifo->unused = ele->next;
        free(ele);
        num_freed++;
    }

    // Since Everyting is Basically Empty 
    // Free the dynamiclly created FIFO
    if(fifo->head == (node_t*)NULL  && fifo->tail == 
        (node_t*)NULL && fifo->unused == (node_t*)NULL) {
        free(fifo);
    }
}