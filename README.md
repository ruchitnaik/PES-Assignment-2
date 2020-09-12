# PES-Assignment-1
Author: Arpit Savarkar

## Repository Comments 
_Contains_
Code for Assignment 2 for PES, ECEN-5813, Fall 2020

Repository for PES-Assignment 1 

- <b>llfifo.h - Header file which contains the function prototypes and enumerators needed for llfifo.c</b>
- <b>llfifo.c - The main script for instantiating and testing a linkedlist based Queue</b>
- <b>cbfifo.h - Header file which contains the function prototypes and enumerators needed for cbfifo.c</b>
- <b>cbfifo.c - The main script for instantiating and testing a Circular Buffer based Queue</b>

## Circular Buffer based Queue
cbfifo.h Involves Four Functions and Unit Tests and helper functions for the following 
1) cbfifo_enqueue(void *buf, size_t nbyte
 - Returns the number of bytes requested to be enqueued on a linkedlist based implementation of a linkedlist. Enqueues data onto the FIFO, up to the limit of the available FIFO capacity The number of bytes actually enqueued, which could be 0. In case of an error, returns -1.

2) cbfifo_dequeue(void *buf, size_t nbyte)
 - Attempts to remove ("dequeue") up to nbyte bytes of data from the FIFO. Removed data will be copied into the buffer pointed to by buf. Returns The number of bytes actually copied, which will be between 0 and nbyte. In case of an error, returns -1.

3) cbfifo_length()
 - Returns the Number of bytes currently available to be dequeued from the FIFO

4) cbfifo_capacity()
 - Returns the capacity, in bytes, for the FIFO

==========================================================================================================
## Linked List Based Queue
1) llfifo_create(int capacity)
 - Initializes the FIFO and A pointer to an llfifo_t, or NULL in case of an error.

2) llfifo_enqueue(llfifo_t *fifo, void *element)
 - Enqueues an element onto the FIFO, growing the FIFO by adding additional elements, if necessary. The new length of the FIFO on success, -1 on failure

3) llfifo_length(llfifo_t *fifo)
 - Returns the number of elements currently on the FIFO. 

4) llfifo_dequeue(llfifo_t *fifo)
 - Removes ("dequeues") an element from the FIFO, and returns it

5) llfifo_capacity(llfifo_t *fifo)
 - Returns The current capacity, in number of elements, for the FIFO

4) llfifo_destroy(llfifo_t *fifo)
 - Teardown function. The llfifo will free all dynamically allocated memory. After calling this function, the fifo should not be used again!

## Assignment Comments 
This assignment demonstrates C Programming from scratch for data representation conversion and FIFO Based implementation using both LinkedList and Ciruclar Buffer, it also demonstrates a code for testing the specified data structures. 

## Execution 
 - To run the Program (Linux) :
1) make
2) ./main
