#include "common.h"
#include <stdio.h>
#include <string.h>
const void *swap(const void *a, const void *b, size_t size) {
  void *tmp = malloc(size);
  if (tmp == NULL) {
    fprintf(stderr, "Error allocating memory");
    exit(EXIT_FAILURE);
  }
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  free(tmp);
  return a;
}

// generic merge function
void merge(void *array, int left, int mid, int right, size_t size,
           int (*compare)(const void *, const void *)) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  printf("merge\n");
  void *L = malloc(n1 * size);
  void *R = malloc(n2 * size);
  if (L == NULL || R == NULL) {
    fprintf(stderr, "Error allocating memory");
    exit(EXIT_FAILURE);
  }
  // tmp array
  memcpy(L, (char *)array + left * size, n1 * size);
  memcpy(R, (char *)array + (mid + 1) * size, n1 * size);

  int i = 0;
  int j = 0;
  int k = left;

  while(i < n1 && j < n2) {
    if(compare((char *) L + i *size, (char *) R + j * size) <= 0){
      memcpy((char *) array + k * size,(char *) L + i * size,size);
      i++;
    } else {
      memcpy((char *) array + k * size,(char *) R + j * size,size);
      j++;
    }
    k++;
  }

  while(i< n2){
    memcpy((char *) array + k* size ,(char *) R + j * size,size);
    j++;
    k++;
  }
  free(L);
  free(R);
}

void merge_sort(void *array,int left,int right, size_t size, int (*compare)(const void *, const void *)){
  printf("merge sort\n");
  if(left < right){
    int mid = left + (right - left) / 2;
    merge_sort(array,left,mid,size,compare);
    merge_sort(array,mid + 1,right,size,compare);
    merge(array,left,mid,right,size,compare);
  }
}

void binary_insertion_sort(void *array,int nitems,size_t size, int (*compare)(const void *,const void *)){
  for(int i =0;i<nitems-1;i++){
    int left = 0;
    int right = i;
    int j = i;
    char *key = (char *) array + j * size;
  while(left <= right){
    int mid = left + (right - left) /2;
    char *mid_element = (char *) array + mid * size;
    int cmp = compare(mid_element,key);
    if(cmp <= 0)
      left = mid + 1;
    else
      right = mid -1;

  }
  for(int k = i;k> left;k--){
    swap((char *) array + (k-1) * size, (char *)array + k*size,size);
  }
  memcpy((char *) array + left * size,key,size);
  }
}

void merge_insertion_sort(void *array, size_t nitems, size_t size, int (*compare)(const void *, const void *)) {
  for(int i = 0;i<nitems-1;i++){
    int left = 0;
    int right = i;
    int j = i;
    char *key = (char *) array + j * size;

    while(left <= right) {
      int mid = left + (right - left) /2;
      char *mid_element = (char *) array + mid * size;
      int cmp = compare(key,mid_element);
      if(cmp <= 0) 
        left = mid +1;
      else 
        right = mid -1;
    }
    for(int k = i;k> left;k--){
      swap((char *) array + (k-1) * size, (char *)array + k*size,size);
    }
  }

}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size,
                                 size_t k,
                                 int (*compare)(const void *, const void *)) {
  int left = 0;
  int right = nitems;
  printf("started merge_binary_insertion_sort with compare function\n");
  printf("k is: %ld\nleft is: %d\nright is %d\n", k,left,right);
  printf("before if");
  if (k <= 0) {
    printf("calling merge_sort\n");
    merge_sort(base, 0, nitems - 1,size, compare);
  } else if (k >= nitems) {
    binary_insertion_sort(base, left, right, compare);
  } else {
    for (size_t i = 0; i < nitems; i += k) {
      size_t end = (i+k <= nitems) ? i+k : nitems;
      binary_insertion_sort(base + i, k, right, compare);
    }
    merge_sort(base, 0, nitems - 1,size, compare);
  }
}
