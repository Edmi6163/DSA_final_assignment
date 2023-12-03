#include "common.h"

int compare_string(const void *a, const void *b)
{
  assert(a != NULL && b != NULL);
  const struct Records *elem_a = (const struct Records *)a;
  const struct Records *elem_b = (const struct Records *)b;
  return strcmp(elem_a->field1, elem_b->field1);
}

int compare_int(const void *a, const void *b)
{
  assert(a != NULL && b != NULL);
  const struct Records *elem_a = (const struct Records *)a; 
  const struct Records *elem_b = (const struct Records *)b;

return (elem_a->field2 < elem_b->field2) - (elem_a->field2 > elem_b->field2);

}

int compare_double(const void *a, const void *b)
{
  assert(a != NULL && b != NULL);
  const struct Records *elem_a = (const struct Records *)a;
  const struct Records *elem_b = (const struct Records *)b;

  return (elem_a->field3 < elem_b->field3) - (elem_a->field3 > elem_b->field3);
  
}