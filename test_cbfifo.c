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
 * @file test_cbfifo.c
 * @brief An abstraction to maintain and instantiate Ciruclar Buffer
 * instantiated globally in cbfifo.h
 * 
 * This file provides functions and abstractions for to test and
 * manipulate Circular Buffer in cbfifo.c
 * 
 * @author Arpit Savarkar
 * @date September 10 2020
 * @version 1.0
 * 
 * 
  Sources of Reference :
  Online Links : https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
  Textbooks : Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers 
  I would like to thank the SA's of the course Rakesh Kumar, Saket Penurkar and Howdy Pierece for their 
  support to debug the Cirular Buffer Implementation
*/

#include "cbfifo.c"

int test_cbfifo_enqueue()
{ 
  typedef struct {
    char element;
    int expected_res;
  } test_matrix_t;
  
  int act_ret;
  char str[11] = "testString";
  char ch = 'a';
  test_matrix_t tests[] =
    { 
      {str[0], 1},
      {str[2], 2},
      {ch, 3}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = cbfifo_enqueue( &tests[i].element, sizeof(tests[i].element));
    if (act_ret == tests[i].expected_res ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: cbfifo_enqueue(fifo, %d) returned %d expected %d ", test_result,
        tests[i].element, act_ret, tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  return (tests_passed == num_tests);
}


int test_cbfifo_capacity()
{ 
  typedef struct {
    int expected_res;
  } test_matrix_t;
  
  test_matrix_t tests[] =
    { 
      {128}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;
  size_t act_ret;
  for(int i=0; i<num_tests; i++) {
    act_ret = cbfifo_capacity();
    if (act_ret == tests[i].expected_res ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: cbfifo_capacity (fifo) returned %ld expected %d ", test_result,
      act_ret, tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  return (tests_passed == num_tests);
}



int test_cbfifo_length()
{ 
  typedef struct {
    int expected_res;
  } test_matrix_t;
  
  test_matrix_t tests[] =
    { 
      {3}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;
  size_t act_ret;
  for(int i=0; i<num_tests; i++) {
    act_ret = cbfifo_length();
    if (act_ret == tests[i].expected_res ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: cbfifo_capacity (fifo) returned %ld expected %d ", test_result,
      act_ret, tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  return (tests_passed == num_tests);
}



int test_cbfifo_dequeue()
{ 
  typedef struct {
    void* element;
    int expected_res;
  } test_matrix_t;
  
  int act_ret;
  char strDump[] = "zzzzzzzzzz";
  
  // The 3 bytes Enqueued in teh cbfifo_enqueue Function and 
  // Dequesed bytes here 
  test_matrix_t tests[] =
    { 
      {strDump, 2},
      {strDump, 1},
      {strDump, 0},
      {strDump, 0}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = cbfifo_dequeue( strDump, 2 );
    if (act_ret == tests[i].expected_res ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: cbfifo_dequeue(strDump, %d) returned %d expected %d ", test_result,
        *(int*)tests[i].element, act_ret, tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  
  // Necesarry Function Since the fucntion is created dynamically 
  // cbfifo_free();
  return (tests_passed == num_tests);
}


int main()
{
    int pass = 0;
    pass = test_cbfifo_enqueue();
    assert(pass);
    pass = test_cbfifo_capacity();
    assert(pass);
    pass = test_cbfifo_length();
    assert(pass);
    pass = test_cbfifo_dequeue();
    assert(pass);
     
    free(fifo->buff);
    cbfifo_free();
    return 0;
}