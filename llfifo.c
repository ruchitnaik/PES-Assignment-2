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
 * @version 1.0
 * 
 * 
  Sources of Reference :
  Online Links : https://github.com/geekfactory/FIFO/blob/master/FIFO.h
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers 
  I would like to thank the SA's of the course Rakesh Kumar, Saket Penurkar and Howdy Pierece for their 
  support to debug the Linkedlist FIFO Implementation
*/

#ifndef _LLFIFO_C_
#define _LLFIFO_C_

#include "llfifo.h"

// Definition of the Node of the Linked List 
typedef struct Node { 
    void* key; 
    struct Node* next; 
} node; 

// Structure definition for LLFIFO
typedef struct llfifo_s { 
    node *front, *rear, *start;
    size_t allocatednodes;
    size_t storednodes;
    int del_nodes;
    bool created;
    bool destroy;
    void* val;
} llfifo_t; 


// Helper Function to setup the nodes
node* newNode(void* ele, size_t capacity, llfifo_t* fifo) 
{   
    if(!fifo->created) {
        
        fifo->start = (node*)malloc( capacity * sizeof(node)); 
        fifo->created = true;
    }
    int loc = llfifo_length(fifo);
    if(loc <= fifo->allocatednodes - 1) {
        node* T = fifo->start;
        T[loc].key = ele;
        T[loc].next = NULL;
        node* temp = &T[loc];
        return temp; 
    }
    else {
        node* temp2 = (node*)malloc(sizeof(node)); 
        temp2->key = ele;
        temp2->next = NULL; 
        return temp2; 
    }
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
    if(capacity >= 0) {
        // Dynamic Allocation of the Base
        llfifo_t* fifo = (llfifo_t*)malloc(sizeof(llfifo_t));
        // Initially No Nodes Stored
        fifo->storednodes = 0;
        fifo->val = NULL;
        fifo->allocatednodes = capacity;
        fifo->front = fifo->rear = NULL; 
        fifo->created = false;
        fifo->destroy = false;
        fifo->del_nodes = 0;
        return fifo;
    }
    else 
        // Error Handling 
        return NULL;
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
    return (fifo->storednodes - fifo->del_nodes);
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
    if( llfifo_length(fifo) > fifo->allocatednodes ) {
        return llfifo_length(fifo);
    }
    else 
        return fifo->allocatednodes;
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
    if(fifo) {
        // Create a new LL node 
        node* temp = newNode(element, fifo->allocatednodes, fifo);

        // If queue is empty, then new node is front and rear both 
        if (fifo->rear == NULL) { 
            fifo->front = fifo->rear = temp; 
            fifo->storednodes++;
            return llfifo_length(fifo);
        } 
        // Add the new node at the end of queue and change rear 
        fifo->rear->next = temp; 
        fifo->rear = temp;
        fifo->storednodes++; 
        return llfifo_length(fifo);
    }
    else {
            return -1;
    }
     
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

    if(!fifo->destroy) {
        fifo->destroy = true;
    }

    if(fifo->del_nodes == fifo->storednodes - 1) {
        node* temp = fifo->front; 
        fifo->val = temp->key;
        fifo->del_nodes++;
        return fifo->val;
    }

    // If queue is empty, return NULL. 
    // if (fifo->storednodes <= 0) {
    if (llfifo_length(fifo) <= 0) {
        fifo->front = NULL;
        fifo->rear = NULL; 
        return NULL; 
    }
    // Store previous front and move front one node ahead 
    node* temp = fifo->front; 
    fifo->front = fifo->front->next; 
    // If front becomes NULL, then change rear also as NULL 
    if (fifo->front == NULL ) {
        fifo->rear = NULL; 
        return NULL; 
    }

    fifo->val = temp->key;
    if(llfifo_capacity(fifo) > fifo->allocatednodes) {
        free(temp);
    }
    fifo->del_nodes++;
    return fifo->val;
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
    if (fifo) {
        while( llfifo_length(fifo) > llfifo_capacity(fifo) ) {
            llfifo_dequeue(fifo); 
        }
        fifo->del_nodes = fifo->storednodes;
        free(fifo->start);
        free(fifo);  
    }
    else {
        free(fifo); 
        return;
    }
}

#endif // _LLFIFO_C_
