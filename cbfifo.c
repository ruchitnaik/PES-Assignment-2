#include "cbfifo.h"

 

typedef struct cbfifo_s { 
    uint8_t * buff;
    size_t head, tail;
    size_t size;
    bool full_status;
    size_t storedbytes;
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
	if(fifo->full_status)
   	{
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

cbfifo_t *cbfifo_create(size_t size) {
    cbfifo_t* fifo = malloc(sizeof(cbfifo_t));
    assert(fifo);
    fifo-> buff = NULL;
    fifo-> size = SIZE;
    fifo->storedbytes = 0;
    cbfifo_reset();
}

void cb_overwrite_overflow(void *data, size_t nbyte)
{   
    const unsigned char* buf = (const unsigned char*) data;
	assert(fifo);
    fifo->buff[fifo->head] = buf;
    update_ptr_status();
}

int cb_handle_overflow(void *data, size_t nbyte)
{
    int r = -1;
    const uint8_t *buf = (const uint8_t*) data;
    assert(fifo);
    if(!cbfifo_full(fifo))
    {
        fifo->buff[fifo->head] = data;
        for(int i =0; i < nbyte; i++) {
            fifo->buff[fifo->head] = buf[i];
            update_ptr_status();
        }
    }
    return r;
}

size_t cbfifo_enqueue(void *buf, size_t nbyte) {

    int r = 0, prev = 0, latest_size = 0;
    assert(buf && nbyte);
    size_t len = cbfifo_length();
    if(len + nbyte > fifo->size)
        return -1;
    else {
        r = cb_handle_overflow(buf, nbyte);
    }

    return (cbfifo_length() - len);
}


size_t cbfifo_dequeue(void *buf, size_t nbyte) {

    uint8_t *buffer = (const uint8_t*) buf;
    assert(fifo && buffer && fifo->buff);
    size_t len = 0;
    int r = -1;
    size_t len = cbfifo_length();
    if(len - nbyte < 0)
        return -1;
    
    for(int i=0; i < nbyte; i++) {
        if(!circular_buf_empty(fifo))
        {
            *buffer = fifo->buff[fifo->tail];
            retreat_pointer(fifo);
            buffer++;
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
            size = (fifo->tail - fifo->head);
        }
        else {
            size = fifo->size + fifo->head - fifo->tail;
        }
    }
}
size_t cbfifo_capacity() {
    return fifo->size;
}

int main() {
    fifo = cbfifo_create(SIZE);
}


