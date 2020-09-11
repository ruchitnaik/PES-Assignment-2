#include "cbfifo.c"

int test_cbfifo_enqueue()
{ 
  typedef struct {
    char element;
    int expected_res;
  } test_matrix_t;
  
  int act_ret;
  char str[] = "testString";
  char ch = 'a';
  test_matrix_t tests[] =
    { 
      {str[0], 1},
      {str[2], 2},
      {ch, 3},
      {NULL, 4}
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
  cbfifo_free();
  free(fifo);
  return (tests_passed == num_tests);
}

int test_cbfifo_dequeue()
{ 
  typedef struct {
    void* element;
    int expected_res;
  } test_matrix_t;
  
  int act_ret;
  char str[] = "testi";
  char strDump[] = "zzzzzzzzzz";
  int len = cbfifo_enqueue( str, sizeof(str));
  printf("\n Stored Bytes: %d",fifo->storedbytes );
  test_matrix_t tests[] =
    { 
      {strDump, 5},
      {strDump, 5},
      {strDump, 0},
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = cbfifo_dequeue( strDump, 5 );
    // printf('\n');
    puts(strDump);
    if (act_ret == tests[i].expected_res ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("\n  %s: cbfifo_dequeue(fifo, 4) returned %d expected %d ", test_result,
         act_ret, tests[i].expected_res);
  }

  printf("\n %s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  cbfifo_free();
  free(fifo);
  return (tests_passed == num_tests);
}


int main()
{
    int pass = 0;
    pass = test_cbfifo_enqueue();
    assert(pass);
    pass = test_cbfifo_dequeue();
    assert(pass);
     
    free(fifo->buff);
    return 0;
}