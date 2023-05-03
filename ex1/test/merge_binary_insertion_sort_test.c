#include "unity.h"
#include "unity_internals.h"
#include "../common.h"
#include <assert.h>

void test_null_array(void)
{
  int *actual = NULL;
  TEST_ASSERT_NULL(actual);
  merge_binary_insertion_sort(actual,0,0,0,compare_int);
  TEST_ASSERT_NULL(actual);
}

void test_int_array(void)
{
  int actual[] = {8,9,78,653,5};
  int expected[] = {5,8,9,78,653};
 merge_binary_insertion_sort(actual,sizeof(actual[0]),5,6,compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,6);
}

void test_string_array(void)
{
  char a[] = "aaaaaa";
  char b[] = "zzz";
  char c[] = "yy";
  char d[] = "cc";
  char e[] = "ab";
  char f[] = "ba";
  char *actual[] = {a,b,c,d,e,f};
  char *expected[] = {a,e,f,d,c,b};
  merge_binary_insertion_sort(actual,sizeof(char*),6,6,compare_string);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected,actual,5);
}

void test_double_array(void)
{
  double actual[] = {8.0,9.0,78.0,653.0,5.0};
  double expected[] = {5.0,8.0,9.0,78.0,653.0};
  merge_binary_insertion_sort(actual,sizeof(actual[0]),5,6,compare_double);
  TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected,actual,6);
}

int main()
{
  UNITY_BEGIN();
  RUN_TEST(test_null_array);
  RUN_TEST(test_int_array);
  RUN_TEST(test_string_array);
  return UNITY_END();
}
