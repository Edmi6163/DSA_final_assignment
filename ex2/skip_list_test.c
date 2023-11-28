#include "skip_list.h"
#include "unity/unity.h"
#include <assert.h>

static int compare_int(const void *a, const void *b) {
    const int int_a = *(const int *) a;
    const int int_b = *(const int *) b;

    return (int_a > int_b) - (int_a < int_b);
}

void test_empty_skiplist(void){
  struct _SkipList *list;
  new_skiplist(&list,10,compare_string);
  TEST_ASSERT_NOT_NULL(list);
  clear_skiplist(&list);
}

void test_search_char_skip_list(void) {

  struct _SkipList *list;
  new_skiplist(&list, 10, compare_string);

  char actual[7] = {'t', 'e', 's', 't', 'i', 'n', 'g'};

  insert_skiplist(list, &actual[0]);
  insert_skiplist(list, &actual[1]);
  insert_skiplist(list, &actual[2]);
  insert_skiplist(list, &actual[3]);
  insert_skiplist(list, &actual[4]);
  insert_skiplist(list, &actual[5]);
  insert_skiplist(list, &actual[6]);

  char to_search[7] = {'t', 'e', 's', 't', 'i', 'n', 'g'};
  TEST_ASSERT_EQUAL_INT(
    0, compare_string(search_skip_list(list, &to_search[0]), &actual[0]));
  TEST_ASSERT_NULL(search_skip_list(list, &to_search[1]));
  TEST_ASSERT_EQUAL_INT(
    0, compare_string(search_skip_list(list, &to_search[2]), &actual[2]));
  TEST_ASSERT_EQUAL_INT(
    0, compare_string(search_skip_list(list, &to_search[4]), &actual[4]));
}



void test_search_skiplist_not_found(void) {
  struct _SkipList *list;
  new_skiplist(&list,10,compare_int);
    int value = 42;
    int search_value = 24;

    insert_skiplist(list, &value);

    const void *result = search_skip_list(list, &search_value);
    TEST_ASSERT_NULL(result);
    clear_skiplist(&list);
}
void test_insert_skiplist(void) {
  struct _SkipList *list;
  new_skiplist(&list,10,compare_int);
    int value = 42;
    insert_skiplist(list, &value);

    const void *result = search_skip_list(list, &value);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(value, *(int *)result);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_empty_skiplist);
  RUN_TEST(test_insert_skiplist);
  RUN_TEST(test_search_skiplist_not_found);
  return UNITY_END();
}
