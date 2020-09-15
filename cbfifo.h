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

/*
 * Helper function to check if the cB is empty 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   none
 */
bool cbfifo_empty();

/*
 * Helper function to update head and tail pointer to keep track of the CB 
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   none
 */
static void update_head_tail();


/*
 * Helper Function to reset tail incase of over flow  
 *
 * Parameters:
 *   none
 * 
 * Returns:
 *   none
 */
static void reset_tail();

/*
 * Helper Function to enque data per byte  
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 * 
 * Returns:
 *   none
 */
void helper_cbenque(void *buf, size_t nbyte);

#endif // _CBFIFO_H_
