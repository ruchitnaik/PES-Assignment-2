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
      {1, fifo}  
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
    } else {
      test_result = "FAILED";
    }

    if ( ( (fifo == NULL) && tests[i].capacity <0)) {
      test_result = "PASSED";
      tests_passed++;
      printf(" \n %s: llfifo_create(%d) returned %d", test_result, tests[i].capacity, fifo);
    } else {
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
  fifo = llfifo_create(6);
  typedef struct {
    void* element;
    int expected_res;
  } test_matrix_t;
  
  int act_ret;
  int temp = 1;
  char c= 'a';
  int temp2 = INT32_MAX;
  test_matrix_t tests[] =
    { 
      {&temp, 1},
      {&c, 2},
      {&temp2, 3},
      {NULL, -1}
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

  printf("%s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  llfifo_destroy(fifo);
  return (tests_passed == num_tests);
}

int test_llfifo_dequeue()
{ 
  llfifo_t* fifo;
  size_t len;
  fifo = llfifo_create(6);
  int temp = 1;
  char c = 'a';
  int temp2 = 20;
  len = llfifo_enqueue(fifo, &temp);
  len = llfifo_enqueue(fifo, &c);
  len = llfifo_enqueue(fifo, &temp2);
  typedef struct {
    int expected_res;
  } test_matrix_t;
  
  void* act_ret;
  test_matrix_t tests[] =
    { 
      {temp},
      {c},
      {temp2},
      {NULL},
      {NULL}
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = llfifo_dequeue(fifo);
    printf("\n%d", i);
    if ( (*((unsigned char*)act_ret) == (unsigned char)tests[i].expected_res) || (act_ret == tests[i].expected_res)  ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    // printf("\n  %s: llfifo_dequeue() returned %d expected %d ", test_result,
    //      *((unsigned char*)act_ret), (unsigned char)tests[i].expected_res);
  }

  // printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  llfifo_destroy(fifo);
  // return (tests_passed == num_tests);
}

int main() {
  int pass = 0;
  // pass = test_llfifo_create();
  // assert(pass);
  // pass = test_llfifo_enqueue();
  // assert(pass);
  test_llfifo_dequeue();
  // assert(pass);
}