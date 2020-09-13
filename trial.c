/******************************************************************************
*​​Copyright​​ (C) ​​2020 ​​by ​​Arpit Savarkar
*​​Redistribution,​​ modification ​​or ​​use ​​of ​​this ​​software ​​in​​source​ ​or ​​binary
*​​forms​​ is​​ permitted​​ as​​ long​​ as​​ the​​ files​​ maintain​​ this​​ copyright.​​ Users​​ are
*​​permitted​​ to ​​modify ​​this ​​and ​​use ​​it ​​to ​​learn ​​about ​​the ​​field​​ of ​​embedded
*​​software. ​​Arpit Savarkar ​​and​ ​the ​​University ​​of ​​Colorado ​​are ​​not​ ​liable ​​for
*​​any ​​misuse ​​of ​​this ​​material.
*
******************************************************************************/ 
/**
 * @file test_llfifo.c
 * @brief An abstraction to test the functionalities of Linked List Based 
 * Queue (FIFO) in llfifo.c 
 * 
 * This file provides functions and abstractions for handling and
 * manipulating Circular Buffer
 * 
 * @author Arpit Savarkar
 * @date September 10 2020
 * @version 1.0
 * 
 * 
  Sources of Reference :
  Online Links : https://github.com/geekfactory/FIFO/blob/master/FIFO.h
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers 
  I would like to thank the SA's of the course Rakesh Kumar, Saket Penurkar and Howdy Pierece for their 
  support to debug the Linkedlist FIFO Implementation
*/

#include "llfifo.c"


int test_llfifo_dequeue()
{ 
  llfifo_t* fifo;
  fifo = llfifo_create(2);
  int a = INT8_MAX;
  int b = INT16_MAX;
  int c = INT32_MAX;
  char str[] = "papiha";

  size_t len = llfifo_enqueue(fifo, &a);
  len = llfifo_enqueue(fifo, &b);
  len = llfifo_enqueue(fifo, &c);
//   len = llfifo_enqueue(fifo, str);
  len = llfifo_enqueue(fifo, &a);
  len = llfifo_enqueue(fifo, &b);
  len = llfifo_enqueue(fifo, &c);
  if(len==0) {
    len = 0;
    return 0;
  }
  typedef struct {
    void* expected_res;
  } test_matrix_t;
  
  void* act_ret;
  test_matrix_t tests[] =
    { 
      {&a},
      {&b},
      {&c},
    //   {str},
      {&a},
      {&b},
      {&c}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = llfifo_dequeue(fifo);
    if ( *(int*)act_ret == *(int*) tests[i].expected_res)  {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: llfifo_dequeue() returned %d expected %d ", test_result,
          *(int*)act_ret, *(int*) tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  llfifo_destroy(fifo);
  return (tests_passed == num_tests);
}


int main() {
  int pass = 1;
//   pass &= test_llfifo_create();
//   pass &= test_llfifo_enqueue();
  pass &= test_llfifo_dequeue();
//   pass &= test_llfifo_capacity();
  
  return pass;
}