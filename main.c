#include "test_llfifo.c"
#include "test_cbfifo.c"

int main() {
    int success = 1;

    success &= llfifo_main();
    success &= cbfifo_main();

    if (success)
        printf("All tests succeeded\n");
    else
        printf("NOTE: FAILURES OCCURRED\n");
    
}