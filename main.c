#ifndef _TEST_LLFIFO_H_
#include "test_llfifo.h"
#endif // _TEST_LLFIFO_H_

#ifndef _TEST_CBFIFO_H_
#include "test_cbfifo.h"
#endif // _TEST_CBFIFO_H_

#include<stdio.h>
int main() {
    int success = 1;

    test_llfifo();
    success &= cbfifo_main();
    if (success)
        printf("All tests succeeded\n");
    else
        printf("NOTE: FAILURES OCCURRED\n");
    
}