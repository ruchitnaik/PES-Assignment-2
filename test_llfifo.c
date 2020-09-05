#include "llfifo.c"

int test_llfifo_create()
{
  typedef struct {
    int val;
    int capacity;
    const llfifo_t *expected_val;
  } test_matrix_t;

  int act_ret;
  test_matrix_t tests[] =
    { 
      {0, -1, NULL},
      {0, 0, NULL},
      {1, 1, 1}  
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = llfifo_create(tests[i].capacity);

    if (act_ret == tests[i].val ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("  %s: llfifo_create(..., %u, %u) returned %d", test_result,
        tests[i].val, tests[i].capacity, act_ret);
  }

  printf("%s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  return (tests_passed == num_tests);
}

int test_llfifo_length()
{
  typedef struct {
    const llfifo_t *expected_val;
  } test_matrix_t;

  llfifo_t act_ret;
  test_matrix_t tests[] =
    { 
      {0, -1, NULL},
      {0, 0, NULL},
      {1, 1, 1}  
    };

  const int num_tests = sizeof(tests) / sizeof(test_matrix_t);
  int tests_passed = 0;
  char *test_result;

  for(int i=0; i<num_tests; i++) {
    act_ret = llfifo_create(tests[i].capacity);

    if (act_ret == tests[i].val ) {
      test_result = "PASSED";
      tests_passed++;
    } else {
      test_result = "FAILED";
    }
    
    printf("  %s: llfifo_create(..., %u, %u) returned %d", test_result,
        tests[i].val, tests[i].capacity, act_ret);
  }

  printf("%s: PASSED %d/%d\n", __FUNCTION__, tests_passed, num_tests);
  return (tests_passed == num_tests);
}