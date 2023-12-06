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
  struct SkipList *list;
  new_skiplist(&list, 10, compare_string);
  TEST_ASSERT_NOT_NULL(list);
  clear_skiplist(&list);
}

void test_clear_skiplist(void) {
  struct SkipList *list;
  new_skiplist(&list, 10, compare_string);
  TEST_ASSERT_NOT_NULL(list);
  clear_skiplist(&list);
  TEST_ASSERT_NULL(list);
}

void test_search_string(void) {
  struct SkipList *list;
  new_skiplist(&list, 10, compare_string);
  char *value = "testing";
  char *search_value = "testing";

  insert_skiplist(list, value);

  const void *res = search_skiplist(list, search_value);
  TEST_ASSERT_NOT_NULL(res);
  TEST_ASSERT_EQUAL_STRING(value, (char *)res);
  clear_skiplist(&list);
}

void test_insert_multiple_string(void) {
  struct SkipList *list;
  new_skiplist(&list, 10, compare_string);
  char *values[] = {"testing", "test", "test1", "10", "multiple", "string"};
  size_t length = sizeof(values) / sizeof(values[0]);

  for (size_t i = 0; i < length; i++) {
    insert_skiplist(list, values[i]);
  }

  for (size_t i = 0; i < length; i++) {
    const void *res = search_skiplist(list, values[i]);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL_STRING(values[i], (char *)res);
  }
}

void test_insert_multiple_int(void) {
  struct SkipList *list;
  new_skiplist(&list, 10, compare_int);
  int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t length = sizeof(values) / sizeof(values[0]);

  for (size_t i = 0; i < length; i++) {
    insert_skiplist(list, &values[i]);
  }

  for (size_t i = 0; i < length; i++) {
    const void *res = search_skiplist(list, &values[i]);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL(values[i], *(int *)res);
  }
}

void test_find_non_existing_value(void) {
  struct SkipList *list;
  new_skiplist(&list, 10, compare_int);
  int non_values = 10;
  int values[] = {-1, 2, 4, 5, 7, 9};
  size_t length = sizeof(values) / sizeof(values[0]);

  for (size_t i = 0; i < length; i++) {
    insert_skiplist(list, &values[i]);
  }

  const void *res = search_skiplist(list, &non_values);
  TEST_ASSERT_NULL(res);
}

void test_search_skiplist_not_found(void) {
  struct SkipList *list;
  new_skiplist(&list, 10, compare_int);
  int value = 42;
  int search_value = 24;

  insert_skiplist(list, &value);

  const void *result = search_skiplist(list, &search_value);
  TEST_ASSERT_NULL(result);
  clear_skiplist(&list);
}
void test_insert_int_skiplist(void) {
  struct SkipList *list;
  new_skiplist(&list, 10, compare_int);
  int value = 42;
  insert_skiplist(list, &value);

  const void *res = search_skiplist(list, &value);
  TEST_ASSERT_NOT_NULL(res);
  TEST_ASSERT_EQUAL(value, *(int *)res);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_search_string);
  RUN_TEST(test_search_skiplist_not_found);
  RUN_TEST(test_insert_multiple_string);
  RUN_TEST(test_insert_multiple_int);
  RUN_TEST(test_find_non_existing_value);
  RUN_TEST(test_insert_int_skiplist);
  RUN_TEST(test_empty_skiplist);
  RUN_TEST(test_clear_skiplist);
  return UNITY_END();
}
