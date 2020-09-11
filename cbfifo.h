/*
 * cbfifo.h - a fixed-size FIFO implemented via a circular buffer
 * 
 * Author: Howdy Pierce, howdy.pierce@colorado.edu
 * 
 */

#ifndef _CBFIFO_H_
#define _CBFIFO_H_

#include <stdlib.h>  // for size_t
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define SIZE 128



/* 
 * The cbfifo's main data structure. 
 *
 * Defined here as an incomplete type, in order to hide the
 * implementation from the user. You will need to define this struct
 * in your .c file.
 */
typedef struct cbfifo_s cbfifo_t;


// cbfifo_t *cbfifo_create(size_t size);

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
size_t cbfifo_enqueue(void *buf, size_t nbyte);


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
size_t cbfifo_dequeue(void *buf, size_t nbyte);


/*
 * Returns the number of bytes currently on the FIFO. 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length();


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity();


#endif // _CBFIFO_H_
