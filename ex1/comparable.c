#include "common.h"

int compare_string(const void *a, const void *b)
{
  assert(a != NULL && b != NULL);
  return strcmp(*(char **)a, *(char **)b);
}

int compare_int(const void *a, const void *b)
{
  assert(a != NULL && b != NULL);
  if(a<b)
    return -1;
  else if(a>b)
    return 1;
  else
    return 0;
}

int compare_double(const void *a, const void *b)
{
  assert(a != NULL && b != NULL);
  if(a<b)
    return -1;
  else if(a>b)
    return 1;
  else
    return 0;
}