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

int test_llfifo_create()
{
  typedef struct {
    int capacity;
    llfifo_t *expected_val;
  } test_matrix_t;

  llfifo_t* fifo =llfifo_create(0);
  test_matrix_t tests[] =
    { 
      {-1, NULL},
      {0, NULL},
      {1, fifo},
      {2, fifo} 
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    fifo = llfifo_create(tests[i].capacity);

    if ((tests[i].capacity >=0) && (fifo !=NULL)) {
      test_result = "PASSED";
      tests_passed++;
      printf(" \n %s: llfifo_create(%d) returned %ld", test_result, tests[i].capacity, fifo->allocatednodes);
    } 
    else if ( ( (fifo == NULL) && tests[i].capacity <0)) {
      test_result = "PASSED";
      tests_passed++;
      printf(" \n %s: llfifo_create(%d) returned NULL", test_result, tests[i].capacity);
    }
    else {
      printf(" \n %s: llfifo_create(%d) returned Illegal size", test_result, tests[i].capacity);
      test_result = "FAILED";
    }

  }

  printf("\n%s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  llfifo_destroy(fifo);
  return (tests_passed == num_tests);
}

int test_llfifo_enqueue()
{ 
  llfifo_t* fifo;
  llfifo_t* gigo;
  fifo = llfifo_create(6);
  gigo = llfifo_create(-1);
  typedef struct {
    void* element;
    int expected_res;
  } test_matrix_t;
  
  int act_ret;
  size_t temp_len = 10;
  act_ret = llfifo_enqueue(gigo, &temp_len);

  if (act_ret == -1 ) {
    printf("\n  PASSED: Enquining to Uninitialized FIFO returned null ");
  } else {
    printf("\n Uninitialized test failed ");
  }

  typedef struct test_struct {
    int x;
    char y;
  } test_st;
  test_st object;
  object.x = 1;
  object.y = 'a';
  test_matrix_t tests[] =
    { 
      {(void*)INT8_MAX, 1},
      {(void*)INT16_MAX, 2},
      {(void*)INT32_MAX, 3},
      {&object, 4},
      {NULL, 5}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = llfifo_enqueue(fifo, tests[i].element);

    if (act_ret == tests[i].expected_res ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: llfifo_enqueue(fifo, %p) returned %d expected %d ", test_result,
        tests[i].element, act_ret, tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  // llfifo_destroy(fifo);
  return (tests_passed == num_tests);
}

int test_llfifo_dequeue()
{ 
  llfifo_t* fifo;
  fifo = llfifo_create(6);
  int a = INT8_MAX;
  int b = INT16_MAX;
  int c = INT32_MAX;
  char str[] = "papiha";

  size_t len = llfifo_enqueue(fifo, &a);
  len = llfifo_enqueue(fifo, &b);
  len = llfifo_enqueue(fifo, &c);
  len = llfifo_enqueue(fifo, str);
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
      {str},
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

int test_llfifo_capacity() {

  llfifo_t* fifo;

  typedef struct {
    int expected_res;
  } test_matrix_t;
  
  int act_ret;
  test_matrix_t tests[] =
    { 
      {1},
      {2},
      {3}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;
  for(int i=0; i<num_tests; i++) {
    fifo = llfifo_create(tests[i].expected_res);
    act_ret = fifo->allocatednodes;
    if ( act_ret ==  tests[i].expected_res)  {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: llfifo_length() returned %d expected %d ", test_result,
          act_ret, tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  llfifo_destroy(fifo);
  return (tests_passed == num_tests);
}

int llfifo_main() {
  int pass = 1;
  pass &= test_llfifo_create();
  pass &= test_llfifo_enqueue();
  pass &= test_llfifo_dequeue();
  pass &= test_llfifo_capacity();
  
  return pass;
}