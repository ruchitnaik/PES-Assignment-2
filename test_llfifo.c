#include "llfifo.c"

int test_llfifo_create()
{
  typedef struct {
    int capacity;
    llfifo_t *expected_val;
  } test_matrix_t;

  llfifo_t* fifo;
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
    printf("\n  PASSED: Enquining to Uninitialized FIFO returned null ", act_ret);
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
  llfifo_destroy(fifo);
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

  size_t len = 0;
  len = llfifo_enqueue(fifo, &a);
  len = llfifo_enqueue(fifo, &b);
  len = llfifo_enqueue(fifo, &c);
  len = llfifo_enqueue(fifo, str);
  len = llfifo_enqueue(fifo, &a);
  len = llfifo_enqueue(fifo, &b);
  len = llfifo_enqueue(fifo, &c);

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
      {NULL},
      {1},
      {2},
      {3}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;
  int val = 1;
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

int main() {
  int pass = 0;
  pass = test_llfifo_create();
  assert(pass);
  pass = test_llfifo_enqueue();
  assert(pass);
  pass = test_llfifo_dequeue();
  assert(pass);
  pass = test_llfifo_capacity();
  assert(pass);
  return 0;
}