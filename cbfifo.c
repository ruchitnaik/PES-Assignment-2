#include "cbfifo.h"

bool created = false;

// Definition
typedef struct cbfifo_s { 
    uint8_t * buff;
    size_t head, tail;
    size_t size;
    bool full_status;
    size_t storedbytes;
    size_t last_nbyte;
} cbfifo_t; 

cbfifo_t* fifo;



// Helper Function
void cbfifo_free()
{
	assert(fifo);
	free(fifo);
}

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
	fifo->full_status = false;
	fifo->tail = (fifo->tail + 1) % fifo->size;
}

void cbfifo_create() {
    // Assigns memory pointer for the Circular Buffer
    fifo = malloc(sizeof(cbfifo_t));
    assert(fifo);
    //Contiguious Dynamic Memory allocation of upto SIZE 
    fifo-> buff = (uint8_t *)malloc(SIZE * sizeof(uint8_t));

    // Dynamic Memory allocation failure handling
    if(fifo-> buff == NULL) {
        exit(0);
    }
    // SIZE of buffer
    fifo-> size = SIZE;
    // Pointer to keep track of the size of the bytes in
    // Circular Buffer 
    fifo->storedbytes = 0;

    // Helper Pointers for CB
    fifo->head = 0;
    fifo->tail = 0;

    fifo->full_status = false;
    fifo->last_nbyte = 0;
    created = true;
}

// Helper Function to enque data per byte
void helper_cbenque(void *buf, size_t nbyte)
{
    if (buf && fifo->buff) {
    // Typecasting to 8 bits
    uint8_t *data = (uint8_t*) buf;
    assert(fifo);

    if(!fifo->full_status) {   

        // Moves the base pointer upto nbytes 
        for(int i =0; i< nbyte ; i++) {
        *(uint8_t*) (fifo->buff + i) = *(uint8_t*) (data + fifo->head);
            update_head_tail();
        }
        }
    }
    

}

size_t cbfifo_enqueue(void *buf, size_t nbyte) {

    //Asserts that the base struct is created which handles 
    //The byte storage
    if (!created) {
    cbfifo_create(); 
    }
    if (buf && created && nbyte>=0 && !fifo->full_status) {

        // assert(buf && nbyte);
        // Checks if the bytes to be inserted exceeds the 
        // max capacity of the Circular Buffer  
        if(cbfifo_length() + nbyte > fifo->size) {
            return -1;
        }
        else {
            helper_cbenque(buf, nbyte);
        }
        return (fifo->storedbytes);
    }
    else {
        return -1;
    }
    
}


size_t cbfifo_dequeue(void *buf, size_t nbyte) {

    uint8_t *buffer = (uint8_t*) buf;
    size_t len=0;
    assert(fifo && buffer);
    for(int i=0; i < nbyte; i++) {
        if(!cbfifo_empty(fifo)) {   
            if(fifo->storedbytes <= 0) {
                cbfifo_free();
                return i;
            }
            *(uint8_t*) (buffer + i) = *(uint8_t*) (fifo->buff + fifo->tail  ) ;
            reset_tail(fifo); 
            fifo->storedbytes = cbfifo_length();
            len++;
        }
    }
    return len;
}

size_t cbfifo_length() {
    
    assert(fifo);
    size_t size = fifo->size;
    if(!fifo->full_status) {
        if(fifo->head >= fifo->tail) {
            size = (fifo->head - fifo->tail);
        }
        else {
            size = fifo->size + fifo->head - fifo->tail;
        }
    }
    return size;
}
size_t cbfifo_capacity() {
    return fifo->size;
}



