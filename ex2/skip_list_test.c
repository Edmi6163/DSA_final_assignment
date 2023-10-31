#include "skip_list.h"
#include "unity/unity.h"
#include <assert.h>

void test_search_char_skip_list(void) {
  struct _SkipList *list = NULL;
  new_skiplist(&list, 10, compare_string);

  char actual[7] = {'t', 'e', 's', 't', 'i', 'n', 'g'};

  insert_skiplist(list, actual + 0);
  insert_skiplist(list, actual + 1);
  insert_skiplist(list, actual + 2);
  insert_skiplist(list, actual + 3);
  insert_skiplist(list, actual + 4);
  insert_skiplist(list, actual + 5);
  insert_skiplist(list, actual + 6);

  char to_search[6] = {'l', 't', 'k', '4', 'g'};
  TEST_ASSERT_EQUAL_INT(
      0, compare_string(search_skip_list(list, to_search + 0), actual + 0));
  TEST_ASSERT_NULL(search_skip_list(list, to_search + 1));
  TEST_ASSERT_EQUAL_INT(
      0, compare_string(search_skip_list(list, to_search + 2), actual + 2));
  TEST_ASSERT_EQUAL_INT(
      0, compare_string(search_skip_list(list, to_search + 4), actual + 4));
}

void test_insert_string_skip_list(void) {
  struct _SkipList *list = malloc(sizeof(struct _SkipList));
  new_skiplist(&list, list->max_height, compare_string);
  char *a = malloc(sizeof(char) * strlen("aaaa") + 1);
  strcpy(a, "aaaa");
  char *b = malloc(sizeof(char) * strlen("sdadfff") + 1);
  strcpy(b, "sdadfff");
  char *c = malloc(sizeof(char) * strlen("ccc,") + 1);
  strcpy(c, "ccc,");
  char *d = malloc(sizeof(char) * strlen(",") + 1);
  strcpy(d, ",");
  char *e = malloc(sizeof(char) * strlen("4") + 1);
  strcpy(e, "4");

  char *actual[5] = {a, b, c, d, e};

  insert_skiplist(list, a);
  insert_skiplist(list, b);
  insert_skiplist(list, c);
  insert_skiplist(list, d);
  insert_skiplist(list, e);

  char *expected[] = {",", "4", "aaaa", "ccc,", "sdadfff"};
  struct Node *tmp = list->head->next[0];

  for (int i = 0; tmp != NULL; tmp = tmp->next[0]) {
    actual[i] = *(char **)tmp->item;
    i++;
  }
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, 5);

  clear_skiplist(&list);
  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_insert_string_skip_list);
  RUN_TEST(test_search_char_skip_list);
  return UNITY_END();
}