#include "common.h"
#include <stdint.h>
#include <string.h>
const void *swap(const void *a, const void *b, size_t size) {
  void *tmp = malloc(size);
  if (tmp == NULL) {
    fprintf(stderr, "Error allocating memory");
    exit(EXIT_FAILURE);
  }
  memcpy(tmp, a, size);
  memcpy((void *)a, b, size);
  memcpy((void *)b, tmp, size);
  free(tmp);
  return a;
}

// generic merge function
void merge(void *array, int left, int mid, int right, size_t size,
           int (*compare)(const void *, const void *)) {

  printf("merging...\n");
  int n1 = mid - left + 1;
  int n2 = right - mid;
  void *L = calloc(n1,size);
  printf("memory address of L is %p\n", L);
  void *R = calloc(n2,size);
  printf("memory address of R is %p\n", R);

  if (L == NULL || R == NULL) {
    fprintf(stderr, "Error allocating memory");
    exit(EXIT_FAILURE);
  }

  memcpy(L, (char *)array + left * size, n1 * size);
  memcpy(R, (char *)array + (mid + 1) * size, n2 * size);


  int i = 0;
  int j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (compare((char *)L + i * size, (char *)R + j * size) <= 0) {
      memcpy((char *)array + k * size, (char *)L + i * size, size);
      i++;
    } else {
      memcpy((char *)array + k * size, (char *)R + j * size, size);
      j++;
    }
    k++;
  }

  while (i < n2) {
    memcpy((char *)array + k * size, (char *)R + j * size, size);
    j++;
    k++;
  }

  while (j < n2) {
    memcpy((char *)array + k * size, (char *)R + j * size, size);
    j++;
    k++;
  }
  free(L);
  free(R);

  printf("ending merging \n");
}

size_t binary_search(void *array, size_t nitems, size_t size,
                     int (*compare)(const void *, const void *)) {
  size_t left = 0;
  size_t right = nitems;
  printf("binary_search\n");

  while (left <= right) {
    size_t mid = left + (right - left) / 2;
    printf("binary search while loop with mid: %ld\n", mid);
    const void *midElement = (char *)array + mid * size;
    int res = compare(midElement, array);
    if (res < 0) {
      right = mid - 1;
    } else if (res > 0) {
      left = mid + 1;
    } else {
      return mid;
    }
  }
  printf("left is %ld\n", left); // FIXME: infinite while loop
  return left;
}

void binary_insertion_sort(void *array, int nitems, size_t size,
                           int (*compare)(const void *, const void *)) {
  printf("binary_insertion_sort \n");
  for (size_t i = 1; i < nitems - 1; i++) {
    printf("in for loop %ld\n", i);
    size_t j = i;
    printf("j is %ld\n", j);
    void *key = (char *)array + j * size;
    printf("key is %p\n", key);

    size_t insertPosition = binary_search(array, j, size, compare);
    printf("insertPosition %ld\n", insertPosition);

    while (j > insertPosition) {
      void *current = (char *)array + (j - 1) * size;
      void *next = (char *)array + j * size;
      printf("swapping %ld %ld\n", j - 1, j);
      swap(current, next, size);
      j--;
    }

    memcpy((char *)array + insertPosition * size, key, size);
  }
}

void merge_insertion_sort(void *array, size_t nitems, size_t size,
                          int (*compare)(const void *, const void *)) {
  size_t mid = nitems / 2;
  void *left = array;
  void *right = (char *)array + mid * size;

  merge_insertion_sort(left, mid, size, compare);
  merge_insertion_sort(right, nitems - mid, size, compare);

  void *temp = malloc(nitems * size);
  if (temp == NULL) {
    fprintf(stderr, "Error allocating memory");
    exit(EXIT_FAILURE);
  }

  size_t i = 0, j = 0, l = 0;

  while (i < mid && j < nitems - mid) {
    if (compare((char *)left + i * size, (char *)right + j * size) <= 0) {
      memcpy((char *)temp + l * size, (char *)left + i * size, size);
      i++;
    } else {
      memcpy((char *)temp + l * size, (char *)right + j * size, size);
      j++;
    }
    l++;
  }

  while (i < mid) {
    memcpy((char *)temp + l * size, (char *)left + i * size, size);
    i++;
    l++;
  }

  while (j < nitems - mid) {
    memcpy((char *)temp + l * size, (char *)right + j * size, size);
    j++;
    l++;
  }

  memcpy(array, temp, nitems * size);
  free(temp);
}

void merge_binary_insertion_sort(void *array, size_t nitems, size_t size,
                                 size_t k,
                                 int (*compare)(const void *, const void *)) {

  int left = 0;
  int right = nitems - 1;

  printf("merge_binary_insertion_sort\n with k %ld\n", k);
  printf("nitems %ld\n", nitems);
  if (nitems <= 1) {
    return;
  }
  if ((right - left) <= k) {
    binary_insertion_sort(array, nitems, size, compare);
  } else if (left < right) {
    size_t mid = left + (right - left) / 2;
    merge_binary_insertion_sort(array, mid, size, k, compare);
    merge_binary_insertion_sort((char *)array + mid * size, nitems - mid - 1,
                                size, k, compare);
    merge(array, left, mid - 1, nitems - 1, size, compare);
  }
}