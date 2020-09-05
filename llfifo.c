#include "llfifo.h"

typedef struct QNode { 
    const unsigned char * key; 
    struct QNode* next; 
} node; 

typedef struct llfifo_s { 
    node *front, *rear, *read;
    size_t allocatednodes;
    size_t storednodes;
} llfifo_t; 

node* newNode(void *k) 
{ 
    node* temp = (node*)malloc(sizeof(node)); 
    temp->key = (const unsigned char *) k; 
    temp->next = NULL; 
    return temp; 
} 

llfifo_t *llfifo_create(int capacity) {
    void* initial_data;
    llfifo_t* fifo = (llfifo_t*)malloc(sizeof(llfifo_t));
    fifo->storednodes = 0;
    fifo->allocatednodes = capacity;
    fifo->front = fifo->rear = fifo->read = NULL; 
    node* temp = newNode(initial_data);
    for(int i=0; i<capacity; i++) {
        if (i==0) {
            if(fifo->rear == NULL) 
                fifo->front = fifo->rear = fifo->read = temp;
        }
        // Add the new node at the end of queue and change rear 
        fifo->rear->next = temp; 
        fifo->rear = temp; 
    }
    return fifo;
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
    int len =0;
    node* curr;
    curr = fifo->front;
    do {
        len++;
        curr = curr->next;
    }while(curr != fifo->rear);
    return len;
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
    return fifo->storednodes;
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
    // Create a new LL node 
    node* temp = newNode(element); 
  
    // If queue is empty, then new node is front and rear both 
    if (fifo->rear == NULL) { 
        fifo->front = fifo->rear = fifo->read = temp; 
    } 
  
    // Add the new node at the end of queue and change rear 
    fifo->rear->next = temp; 
    fifo->rear = temp;
    fifo->storednodes++; 

    return llfifo_capacity(fifo); 
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
    // If queue is empty, return NULL. 
    if (fifo->read == NULL) 
        return NULL; 
  
    // Store previous front and move front one node ahead 
    node* temp = fifo->read; 
    fifo->read = fifo->read->next; 
  
    // If front becomes NULL, then change rear also as NULL 
    if (fifo->read == NULL) 
        fifo->rear = NULL; 
    fifo->storednodes--;
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
    // If queue is empty, return NULL. 
    if (fifo->front == NULL) 
        return NULL;
    for(int i =0; i<llfifo_capacity(fifo); i++) {
        node* temp = fifo->front;
        fifo->front = fifo->front->next;
        // If front becomes NULL, then change rear also as NULL 
        if (fifo->front == NULL) 
            fifo->rear = NULL; 
        free(temp);
    }
}

// typedef struct llfifo_s {
    
//     void* element_space; // Start Address on memory for item space
//     size_t itemsize; // Size in bytes for each element in the buffer 
//     size_t allocatedbytes; // Size in bytes of the whole buffer 
//     volatile uint16_t read; // Memory offset where data will be read 
//     volatile uint16_t write; // Mem offset where data will be written 
//     volatile size_t storedbytes; // Number of bytes currently by stored items
// } llfifo_t;

// // static void llfifo_copy_from(llfifo_t*, void *);
// // static void llfifo_copy_to(llfifo_t*, const void *);


// /*
//  * Initializes the FIFO
//  *
//  * Parameters:
//  *   capacity  the initial size of the fifo, in number of elements
//  * 
//  * Returns:
//  *   A pointer to an llfifo_t, or NULL in case of an error.
//  */
// llfifo_t *llfifo_create(int capacity) {
//     llfifo_t* llfifo;
//     if (capacity > 0) {
//         llfifo = (llfifo_t *) malloc(sizeof(llfifo_t));
//         size_t bsize = capacity*sizeof(char);
//         llfifo->element_space = malloc(bsize);
//         if (llfifo->element_space != NULL) {
//             llfifo->itemsize = sizeof(char);
//             llfifo->allocatedbytes = bsize;
//             llfifo->read = 0;
//             llfifo->write = 0;
//             llfifo-> storedbytes = 0;
            
//         return llfifo;
//         }
//         else {
//             free(llfifo); // Replace with llfifo_destroy
//         }
//     }
//     return NULL;
// }

// bool llfifo_is_full(llfifo_t* fifo)
// {
// 	if (fifo->storedbytes >= fifo->allocatedbytes)
// 		return true;
// 	else
// 		return false;
// }

// bool llfifo_is_empty(llfifo_t* fifo)
// {
// 	if (fifo->storedbytes == 0)
// 		return true;
// 	else
// 		return false;
// }

// void custum_memcpy(void *dest, void *src, size_t n) 
// { 
//    // Typecast src and dest addresses to (char *) 
//    char *csrc = (char *)src; 
//    char *cdest = (char *)dest; 
  
//    // Copy contents of src[] to dest[] 
//    for (int i=0; i<n; i++) 
//        cdest[i] = csrc[i]; 
// } 

// int llfifo_enqueue(llfifo_t *fifo, void *element)
// {
// 	const unsigned char * pc = (const unsigned char *)element;
//     size_t len = 0;
//     for(int i =0; pc[i]!=NULL; i++) // Wrong logic 
//         len+=sizeof(pc[i]);
    
//     if(fifo->storedbytes+len > fifo->allocatedbytes) {
//         fifo->element_space = realloc(fifo->element_space, fifo->allocatedbytes+len);
//     }
// 	custom_memcpy(fifo->element_space + fifo->write, element, len);
// 	fifo->write += len;
//     fifo->storedbytes += fifo->itemsize;
//     return (llfifo_length(fifo));
// }

// void *llfifo_dequeue(llfifo_t *fifo) {
    
//     if(llfifo_is_empty(fifo)) {
//         return NULL;
//     }

//     fifo->read = (fifo->read + fifo->itemsize) % (fifo->allocatedbytes);
//     void * element;
//     custom_memcpy(element, fifo->element_space + fifo->read, fifo->itemsize);
//     if (fifo->read >= fifo->allocatedbytes) {
// 		fifo->read = 0;
// 	}
// 	fifo->storedbytes -= fifo->itemsize; // Drop stored bytes number by 1 byte
	
//     return element;
// }

// int llfifo_capacity(llfifo_t *fifo) {
//     return fifo->storedbytes;
// }

// void llfifo_destroy(llfifo_t *fifo) {
//     free(fifo->element_space);
//     fifo->itemsize = 0;
//     fifo->allocatedbytes = 0;
//     fifo->read = 0;
//     fifo->write = 0;
//     fifo-> storedbytes = 0;
//     free(fifo);
// }
