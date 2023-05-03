#include "unity.h"
#include "unity_internals.h"
#include "../common.h"
#include <assert.h>

void test_null_array(void)
{
  int *actual = NULL;
  TEST_ASSERT_NULL(actual);
  binary_insertion_sort(actual,0,0,compare_int);
  TEST_ASSERT_NULL(actual);
}

void test_int_array(void)
{
  int actual[] = {8,9,78,653,5};
  int expected[] = {5,8,9,78,653};
  binary_insertion_sort(actual,sizeof(actual[0]),5,compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,6);
}

void test_string_array(void)
{
  char a[] = "aaaaaa";


  TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected,actual,5);
}

int main()
{
  UNITY_BEGIN();
  RUN_TEST(test_null_array);
  RUN_TEST(test_int_array);
  return UNITY_END();
}
