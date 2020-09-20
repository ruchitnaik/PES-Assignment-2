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
    bool is_dynamic;
    struct Node* next; 
} node; 

// Structure definition for LLFIFO
typedef struct llfifo_s { 
    node *front, *rear, *start, *del;
    size_t allocatednodes;
    size_t storednodes;
    int del_nodes;
    bool created;
    bool destroy;
    size_t cap; // Extra Capacity Storage
} llfifo_t; 


// Helper Function to setup the nodes
node* newNode(void* ele, size_t capacity, llfifo_t* fifo)  {   

    if(!fifo->created ) {
        fifo->start = (node*)malloc( capacity * sizeof(node)); 
        fifo->front = NULL; 
        fifo->rear = NULL;
        fifo->created = true;
        fifo->storednodes = 0;
    }
    // int loc = llfifo_length(fifo);
    if(fifo->storednodes)
    int loc = fifo->storednodes;
    if(loc <= fifo->allocatednodes - 1 && capacity != 0 ) {
        printf("\n LOC: %d", loc);
        printf("\n INSIDE");
        node* T = fifo->start;
        assert(fifo->start);
        T[loc].key = ele;
        T[loc].next = NULL;
        T[loc].is_dynamic = false;
        return &T[loc]; 
    }
    else {
        printf("\n OUTSIDE");
        node* temp2 = (node*)malloc(sizeof(node)); 
        temp2->key = ele;
        temp2->next = NULL; 
        temp2->is_dynamic = true;
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
        assert(fifo);
        // Initially No Nodes Stored
        fifo->storednodes = 0;
        fifo->allocatednodes = capacity;
        fifo->cap = 0;
        fifo->front = NULL; 
        fifo->rear = NULL; 
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
    int count = 0;  // Initialize count 
    node* current = fifo->rear;  // Initialize current 
    while (current != NULL) 
    { 
        count++; 
        current = current->next; 
    } 
    return count; 
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
    // if( llfifo_length(fifo) >= fifo->allocatednodes ) {
    if( fifo->cap >= fifo->allocatednodes ) {
        // printf("\n Allocated Nodes %d", fifo->allocatednodes);
        // printf("\n Cap %d", fifo->cap);
        return fifo->cap;
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
        printf("\n Enqueing");
        printf("\n Stored Nodes: %ld", fifo->storednodes);
        // If queue is empty, then new node is front and rear both 
        if (fifo->rear == NULL) { 
            printf("\n DEfronting");
            fifo->rear = fifo->front = temp;
            fifo->del = temp;
            fifo->storednodes++;
        } 
        else {
            printf("\n Fronting");
            // Add the new node at the end of queue and change rear 
            fifo->front->next = temp;
            fifo->front = temp;
            fifo->storednodes++;
        }

        if(fifo->storednodes >= fifo->cap)
            fifo->cap = fifo->storednodes;
        
        return (llfifo_length(fifo));
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
        if (fifo->storednodes == 0)
            return NULL;
    }
    
    node* temp;
    void* ret = fifo->rear->key;

    temp = fifo->rear;
    fifo->rear = fifo->rear->next;
    fifo->storednodes--;


    // If queue is empty, return NULL. 
    if (fifo->rear == NULL) {
        printf("\n REAR OBV IS NULL");
        fifo->storednodes = 0;
        return NULL; 
    }

    // Store previous front and move front one node ahead 

    node* temp = fifo->rear;
    fifo->rear = fifo->rear->next; 
    fifo->storednodes--;
    // If rear becomes NULL, then change front also as NULL 
    if (fifo->rear == NULL) {
        fifo->front = NULL;
        printf("\n REAR IS NULL");
        fifo->storednodes = 0;
    }


    if(temp->is_dynamic == true) {
        free(temp);
    }
    return ret;
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
    int counter = 0;
    if (fifo) {
        while(llfifo_length(fifo) > fifo->allocatednodes)
            llfifo_dequeue(fifo);

        // printf("\n Freeing Data starting from %c", *(char*)fifo->del->key);
        free(fifo->start);
        free(fifo); 
    }
    else {
        free(fifo); 
        return;
    }
}

#endif // _LLFIFO_C_
