#include "unity.h"
#include "unity_internals.h"
#include "../common.h"
#include <assert.h>

void test_int_array_with_k_six(void)
{
  static int actual[] = {8,9,78,653,5};
  static int expected[] = {5,8,9,78,653};
 merge_binary_insertion_sort(actual,5,sizeof(actual[0]),6,compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,6);
}

void test_string_array_with_key_six(void)
{
  static char a[] = "aaaaaa";
  static char b[] = "zzz";
  static char c[] = "yy";
  static char d[] = "cc";
  static char e[] = "ab";
  static char f[] = "ba";
  static char *actual[] = {a,b,c,d,e,f};
  static char *expected[] = {a,e,f,d,c,b};
  merge_binary_insertion_sort(actual,6,sizeof(char *),6,compare_string);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected,actual,5);
}

void test_double_array_with_k_six(void)
{
  static double actual[] = {8.0,9.0,78.0,653.0,5.0};
  static double expected[] = {5.0,8.0,9.0,78.0,653.0};
  merge_binary_insertion_sort(actual,5,sizeof(actual[0]),6,compare_double);
  TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected,actual,6);
}

void test_int_array_with_k_one(void)
{
  static int actual[] = {8,9,78,653,5};
  static int expected[] = {5,8,9,78,653};
 merge_binary_insertion_sort(actual,5,sizeof(actual[0]),1,compare_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(expected,actual,6);
}

void test_string_array_with_key_one(void)
{
 static char a[] = "aaaaaa";
 static char b[] = "zzz";
 static char c[] = "yy";
 static char d[] = "cc";
 static char e[] = "ab";
 static char f[] = "ba";
 static char *actual[] = {a,b,c,d,e,f};
 static char *expected[] = {a,e,f,d,c,b};
  merge_binary_insertion_sort(actual,6,sizeof(actual[0]),1,compare_string);
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected,actual,5);
}

void test_double_array_with_k_one(void)
{
  static double actual[] = {8.0,9.0,78.0,653.0,5.0};
  static double expected[] = {5.0,8.0,9.0,78.0,653.0};
  merge_binary_insertion_sort(actual,5,sizeof(actual[0]),1,compare_double);
  TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected,actual,6);
}

int main()
{
  UNITY_BEGIN();
  RUN_TEST(test_string_array_with_key_one);
  RUN_TEST(test_int_array_with_k_one);
  RUN_TEST(test_double_array_with_k_one);
  RUN_TEST(test_int_array_with_k_six);
  RUN_TEST(test_string_array_with_key_six);
  RUN_TEST(test_double_array_with_k_six);

  return UNITY_END();
}
