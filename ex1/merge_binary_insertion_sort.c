#include "common.h"

/**
 * Generic merge function used by merge sort.
 * @param array The array to be sorted.
 * @param mid The index of the middle element.
 * @param right The index of the rightmost element.
 * @param size The size of each element in the array.
 * @param compare The comparison function used to compare two elements.
 */
void merge(void *array, size_t mid, size_t right, size_t size,
           int (*compare)(const void *, const void *)) {

  void *copy = malloc(right * size);
  memcpy(copy, array, right * size);
  char *L = (char *)copy;
  char *Lend = L + mid * size;
  char *R = Lend;
  char *Rend = L + right * size;

  char *p = (char *)array;
  for (size_t i = 0; i < right; ++i) {
    if (L == Lend) {
      memcpy(p, R, size);
      R += size;
    } else if (R == Rend) {
      memcpy(p, L, size);
      L += size;
    } else if (compare(L, R) < 0) {
      memcpy(p, L, size);
      L += size;
    } else {
      memcpy(p, R, size);
      R += size;
    }
    p += size;
  }
  free(copy);
}

size_t binary_search(void *elem, void *array, size_t nitems, size_t size,
                     int (*compare)(const void *, const void *)) {
  size_t left = 0;
  size_t right = nitems;

  while (left < right) {
    size_t mid = left + (right - left) / 2;
    if (compare((char *)array + mid * size, elem) < 0) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return left;
}

void binary_insertion_sort(void *array, int nitems, size_t size,
                           int (*compare)(const void *, const void *)) {
  void *tmp = malloc(size);
  for (int i = 1; i < nitems; ++i) {
    size_t pos =
        binary_search((char *)array + i * size, array, i, size, compare);
    memcpy(tmp, (char *)array + i * size, size);
    memmove((char *)array + (pos + 1) * size, (char *)array + pos * size,
            (i - pos) * size);
    memcpy((char *)array + pos * size, tmp, size);
  }
  free(tmp);
}

void merge_sort(void *array, void *tmp, size_t left, size_t right, size_t size,
                size_t k, int (*compare)(const void *, const void *)) {
  if (left >= right) {
    return;
  }

  size_t middle = left + (right - left) / 2;
  merge_sort(array, tmp, left, middle, size, k, compare);
  merge_sort(array, tmp, middle + 1, right, size, k, compare);

  void *middle_element = (char *)array + middle * size;
  void *middle_plus_one_element = (char *)array + (middle + 1) * size;
  if (compare(middle_element, middle_plus_one_element) > 0) {
    size_t split = middle - left + 1;
    size_t nitems = right - left + 1;
    merge(array, split, nitems, size, compare);
  }
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size,
                                 size_t k,
                                 int (*compare)(const void *, const void *)) {

  if (nitems <= 1) {
    return;
  }

  if (nitems <= k) {
    binary_insertion_sort(base, nitems, size, compare);
    return;
  }

  size_t mid = nitems / 2;
  merge_binary_insertion_sort(base, mid, size, k, compare);
  merge_binary_insertion_sort(((char *)base) + mid * size, nitems - mid, size,
                              k, compare);
  merge(base, mid, nitems, size, compare);
}