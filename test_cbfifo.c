
#include "cbfifo.c"

int test_cbfifo_enqueue() {

    char buf[] = "this";
    size_t len = cbfifo_enqueue(buf, sizeof(buf));
    printf("\n Size: %ld ", len);
    printf("\n");
    char str[] = "zzzzzzzz";
    puts(str);
    len = cbfifo_dequeue(str, sizeof(buf));
    puts(str);
    printf("\n Size: %ld ", len);

    

}

int main()
{
    test_cbfifo_enqueue(); 
    free(fifo->buff);
    return 0;
}