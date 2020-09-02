#include <stdint.h>
#include <stdlib.h>
#include "cbfifo.h"

uint8_t cur_size(cbfifo_t * buf) {
    return buf->length;
}



size_t cbfifo_enqueue(void *buf, size_t nbyte);


size_t cbfifo_dequeue(void *buf, size_t nbyte);


size_t cbfifo_length();
size_t cbfifo_capacity();


