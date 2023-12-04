#include "skip_list.h"
#include "unity/unity.h"
#include "unity/unity_internals.h"
#include <assert.h>

static int compare_int(const void *a, const void *b) {
  const int int_a = *(const int *)a;
  const int int_b = *(const int *)b;

  return (int_a > int_b) - (int_a < int_b);
}

void test_empty_skiplist(void) {
  struct _SkipList *list;
  new_skiplist(&list, 10, compare_string);
  TEST_ASSERT_NOT_NULL(list);
  clear_skiplist(&list);
}

void test_clear_skiplist(void) {
  struct _SkipList *list;
  new_skiplist(&list, 10, compare_string);
  TEST_ASSERT_NOT_NULL(list);
  clear_skiplist(&list);
  TEST_ASSERT_NULL(list);
}

void test_search_string(void) {
  struct _SkipList *list;
  new_skiplist(&list, 10, compare_string);
  char *value = "testing";
  char *search_value = "testing";

  insert_skiplist(list, value);

  const void *result = search_skip_list(list, search_value);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL_STRING(value, (char *)result);
  clear_skiplist(&list);
}


void test_search_skiplist_not_found(void) {
  struct _SkipList *list;
  new_skiplist(&list, 10, compare_int);
  int value = 42;
  int search_value = 24;

  insert_skiplist(list, &value);

  const void *result = search_skip_list(list, &search_value);
  TEST_ASSERT_NULL(result);
  clear_skiplist(&list);
}
void test_insert_int_skiplist(void) {
  struct _SkipList *list;
  new_skiplist(&list, 10, compare_int);
  int value = 42;
  insert_skiplist(list, &value);

  const void *result = search_skip_list(list, &value);
  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_EQUAL(value, *(int *)result);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_search_string);
  RUN_TEST(test_search_skiplist_not_found);
  RUN_TEST(test_insert_int_skiplist);
  RUN_TEST(test_empty_skiplist);
  RUN_TEST(test_clear_skiplist);
  return UNITY_END();
}
