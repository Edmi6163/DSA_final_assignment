#include "common.h"

void merge(void *array, int left, int mid, int right, int (*compare)(const void *, const void *))
{
  int k;
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int L[n1], R[n2];
  for (int i = 0; i < n1; i++)
  {
    L[i] = array[left + i];
  }
  for (int j = 0; j < n2; j++)
  {
    R[j] = array[mid + 1 + j];
  }
  int i = 0;
  int j = 0;
  k = left;
  while (i < n1 && j < n2)
  {
    if (compare(&L[i], &R[j]) <= 0)
    {
      array[k] = L[i];
      i++;
    }
    else
    {
      array[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1)
  {
    array[k] = L[i];
    i++;
    k++;
  }
  while (j < n2)
  {
    array[k] = R[j];
    j++;
    k++;
  }
}
void *binary_search(void *array, size_t size, int key, int (*compare)(const void *, const void *))
{
  assert(array != NULL && size > 0);
  int left = 0;
  int right = size - 1;
  int mid = (left + right) / 2;
  while (left <= right)
  {
    if (compare(&key, &array[mid]) == 0)
    {
      return &array[mid];
    }
    else if (compare(&key, &array[mid]) < 0)
    {
      right = mid - 1;
    }
    else
    {
      left = mid + 1;
    }
    mid = (left + right) / 2;
  }
  return mid;
}

void merge_sort(void *array, int left, int right, int (*compare)(const void *, const void *))
{
  assert(array != NULL && right > 0);
  if (left < right)
  {
    int mid = (left + right) / 2;
    merge_sort(array, left, mid, compare);
    merge_sort(array, mid + 1, right, compare);
    merge(array, left, mid, right, compare);
  }
}

void binary_insertion_sort(void *array, int left,int right,int (*compare) (const void*,const void*))
{
  assert(array != NULL && right > 0);
  int i, j;
  for (i = 1; i < right; i++)
  {
    int key = array[i];
    int *pos = binary_search(array, right, key, compare);
    if (pos != NULL)
    {
      for (j = i - 1; j >= pos - array; j--)
      {
        array[j + 1] = array[j];
      }
      array[pos - array] = key;
    }
  }
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compare)(const void *, const void *))
{
  assert(base != NULL && size > 0);
  int left = 0;
  int right = nitems - 1;
  if (k <= 0)
  {
    merge_sort(base, 0, nitems - 1, compare);
  }
  else if (k >= nitems)
  {
    binary_insertion_sort(base,left, right, compare);
  }
  else
  {
    for (int i = 0; i < nitems; i += k)
    {
      binary_insertion_sort(base + i, k,right, compare);
    }
    merge_sort(base, 0, nitems - 1, compare);
  }
}
