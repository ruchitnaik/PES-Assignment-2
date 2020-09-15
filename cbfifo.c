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
 * @file cbfifo.c
 * @brief An abstraction to maintain and instantiate Ciruclar Buffer 
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
  Online Links : https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers 
  I would like to thank the SA's of the course Rakesh Kumar, Saket Penurkar and Howdy Pierece for their 
  support to debug the Cirular Buffer Implementation
*/

#ifndef _CBFIFO_C_
#define _CBFIFO_C_

#include "cbfifo.h"


// Checks for Global Bool Status
bool created = false;

// Definition
typedef struct cbfifo_s { 
    uint8_t * buff;
    size_t head, tail;
    size_t size;
    bool full_status;
    size_t storedbytes;
} cbfifo_t; 

cbfifo_t my_fifo;
cbfifo_t* fifo = &my_fifo;
uint8_t CBbuffer[SIZE];


// Helper Function
bool cbfifo_empty()
{
	assert(fifo);
    return (!fifo->full_status && (fifo->head == fifo->tail));
}

// Helper Function
static void update_head_tail()
{
	assert(fifo);
	if(fifo->full_status) {
		fifo->tail = (fifo->tail + 1) % fifo->size;
	}
	fifo->head = (fifo->head + 1) % fifo->size;
	fifo->full_status = (fifo->head == fifo->tail);
    fifo->storedbytes = cbfifo_length();
}

// Helper Function
static void reset_tail()
{
	assert(fifo);
    // Updates the full status 
	fifo->full_status = false;
    // Since it is a cirular buffer if it resizes to 
    // back to position zero if the tail size overFlows
	fifo->tail = (fifo->tail + 1) % fifo->size;
}

void cbfifo_create() {
    // // Assigns memory pointer for the Circular Buffer
    // fifo = (cbfifo_t*)malloc(sizeof(cbfifo_t));
    //Contiguious Dynamic Memory allocation of upto SIZE 
    // fifo-> buff = (uint8_t *)malloc(SIZE * sizeof(uint8_t));
    fifo-> buff = CBbuffer;
    // Dynamic Memory allocation failure handling
    for(int i = 0; i < SIZE; i++)
        fifo-> buff[i] = 0;
    if(fifo-> buff == NULL) {
        exit(0);
    }
    // SIZE of buffer
    fifo-> size = SIZE;
    // Pointer to keep track of the size of the bytes in
    // Circular Buffer 
    fifo->storedbytes = 0;

    // Helper Pointers for circular buffer 
    fifo->head = 0;
    fifo->tail = 0;

    fifo->full_status = false;
    created = true;
}

// Helper Function to enque data per byte
void helper_cbenque(void *buf, size_t nbyte)
{
    if (buf && fifo->buff) {
    // Typecasting to 8 bits
    uint8_t *data = (uint8_t*) buf;
    assert(fifo);
    /* If the Size if not full continue to add on the byte 
     corresponding to head and update the head and the 
     tail pointer */
    if(!fifo->full_status) {   

        // Moves the base pointer upto nbytes 
        for(int i =0; i< nbyte ; i++) {
            fifo->buff[fifo->head] = *(uint8_t*) (data + i);
            update_head_tail();
        }
        }
    }

}


/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 * 
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns -1.
 */
size_t cbfifo_enqueue(void *buf, size_t nbyte) {

    //Asserts that the base struct is created which handles 
    //The byte storage
    if (!created) {
    cbfifo_create(); 
    }
    // Checks for assertions 
    if (buf && created && nbyte>=0 && !fifo->full_status) {

        // Checks if the bytes to be inserted exceeds the 
        // max capacity of the Circular Buffer  
        if(cbfifo_length() + nbyte > fifo->size) {
            // Error Handling 
            return -1;
        }
        else {
            // Helper Function call to Enqueue 
            helper_cbenque(buf, nbyte);
        }
        return (fifo->storedbytes);
    }
    else {
        return -1;
    }
    
}


/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 * 
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 *  nbyte. In case of an error, returns -1.
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte) {

    uint8_t *buffer = (uint8_t*) buf;
    size_t len=0;
    assert(fifo && buffer);
    for(uint8_t i=0; i < nbyte; i++) {
        // Cannot Dequeue from an empty buffer
        if(!cbfifo_empty(fifo)) {   
            // Stored bytes checks the size of the
            // Buffer 
            if(fifo->storedbytes <= 0) {
                // cbfifo_free();
                return i;
            }
            // Dequues from the front where the tail is 
            *(uint8_t*) (buffer + i) = fifo->buff[fifo->tail];
            // Updated tail status 
            reset_tail(fifo); 
            // Stores the current length
            fifo->storedbytes = cbfifo_length();
            len++;
        }
    }
    // Returns the number of bytes Dequeued 
    return len;
}


/*
 * Returns the number of bytes currently on the FIFO. 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length() {
    
    assert(fifo);
    size_t size = fifo->size;
    if(!fifo->full_status) {
        if(fifo->head >= fifo->tail) {
            // When Head is ahead of Tail
            size = (fifo->head - fifo->tail);
        }
        else {
            // When Tail is ahead of head
            size = fifo->size + fifo->head - fifo->tail;
        }
    }
    // Size of the circular buffer 
    return size;
}


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity() {
    // The Max capacity of the circular buffer 
    return fifo->size;
}



#endif // _CBFIFO_C_


