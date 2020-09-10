#include "cbfifo.h"

bool created = false;

typedef struct cbfifo_s { 
    uint8_t * buff;
    size_t head, tail;
    size_t size;
    bool full_status;
    size_t storedbytes;
    size_t last_nbyte;
} cbfifo_t; 

cbfifo_t* fifo;


bool cbfifo_full()
{
	assert(fifo);
    return fifo->full_status;
}

void cbfifo_free()
{
	assert(fifo);
	free(fifo);
}

bool cbfifo_empty()
{
	assert(fifo);
    return (!fifo->full_status && (fifo->head == fifo->tail));
}

void cbfifo_reset()
{
    assert(fifo);
    fifo->head = 0;
    fifo->tail = 0;
    fifo->full_status = false;
}

static void update_ptr_status()
{
	assert(fifo);
	if(fifo->full_status) {
		fifo->tail = (fifo->tail + 1) % fifo->size;
	}
	fifo->head = (fifo->head + 1) % fifo->size;
	fifo->full_status = (fifo->head == fifo->tail);
    fifo->storedbytes = cbfifo_length();
}

static void retreat_pointer()
{
	assert(fifo);
	fifo->full_status = false;
	fifo->tail = (fifo->tail + 1) % fifo->size;
}

void cbfifo_create() {

    fifo = malloc(sizeof(cbfifo_t));
    assert(fifo);
    fifo-> buff = (uint8_t *)malloc(SIZE * sizeof(uint8_t));
    if(fifo-> buff == NULL) {
        exit(0);
    }
    fifo-> size = SIZE;
    fifo->storedbytes = 0;
    fifo->head = 0;
    fifo->tail = 0;
    fifo->full_status = false;
    fifo->last_nbyte = 0;
    created = true;
}


int cb_handle_overflow(void *buf, size_t nbyte)
{
    int r = 0;
    if (buf && fifo->buff) {
    uint8_t *data = (uint8_t*) buf;
    assert(fifo);
    if(!cbfifo_full(fifo))
    {
        for(int i =0; *(uint8_t*) (data + i) != '\0' ; i++) {
           *(uint8_t*) (fifo->buff + i) = *(uint8_t*) (data + fifo->head);
            update_ptr_status();
            r++;
        }
        fifo->last_nbyte = r;
    }
    return r;
    }

}

size_t cbfifo_enqueue(void *buf, size_t nbyte) {

    if (!created) {
    cbfifo_create(); 
    }
    if (created) {

        int r = 0;
        assert(buf && nbyte);
        size_t len = cbfifo_length();
        if(len + nbyte > fifo->size) {
            return -1;
        }
        else {
            r = cb_handle_overflow(buf, nbyte);
        }
        // free(fifo->buff);
        return (fifo->storedbytes);
        
    }
}


size_t cbfifo_dequeue(void *buf, size_t nbyte) {

    uint8_t *buffer = (uint8_t*) buf;
    assert(fifo && buffer && fifo->buff);
    size_t len = cbfifo_length();
    if(len - nbyte < 0)
        return -1;
    
    for(int i=0; i < nbyte; i++) {
        if(!cbfifo_empty(fifo))
        {
            *(uint8_t*) (buffer + i) = *(uint8_t*) (fifo->buff + fifo->tail  ) ;
            retreat_pointer(fifo);
            len--;
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



