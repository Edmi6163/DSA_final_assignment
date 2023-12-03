#include "generic_comparable.h"
int is_null(const void *a, const void *b, int *res) {
  if (a != NULL && b != NULL)
    return 0;
  if (a == NULL && b == NULL)
    *res = 0;
  *res = a == NULL ? -1 : 1;
  return 1;
}

int compare_string_test(const void *a, const void *b)
{
  int res;
  if (is_null(a, b, &res)) return res;
  
  char *v1 = *(char**)a;
  char *v2 = *(char**)b;
  return strcmp(v1, v2);
}


int compare_double_test(const void *a, const void *b)
{
  int res;
  if (is_null(a, b, &res)) return res;
  
  double v1 = *(double*)a;
  double v2 = *(double*)b;
  if(v1<v2) return -1;
  if(v1>v2) return 1;
  return 0;
}

int compare_int_test(const void *a, const void *b) {
  int res;
  if (is_null(a, b, &res))
    return res;

  int v1 = *(int *)a;
  int v2 = *(int *)b;
  if (v1 < v2)
    return -1;
  if (v1 > v2)
    return 1;
  return 0;
}
