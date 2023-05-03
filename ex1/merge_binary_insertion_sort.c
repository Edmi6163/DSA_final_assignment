#include "common.h"
void* swap(const void *a,const void *b,size_t size)
{
  void *tmp = malloc(size);
  memcpy(tmp,a,size);
  memcpy(a,b,size);
  memcpy(b,tmp,size);
  free(tmp);
  return a;
}

//generic merge function
void *merge(void *array, int left, int mid, int right, int (*compare)(const void *, const void *))
{
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;
  void *L = malloc(n1 * sizeof(int));
  void *R = malloc(n2 * sizeof(int));
  if (L == NULL || R == NULL)
  {
    fprintf(stderr, "Error allocating memory");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < n1; i++)
  {
    memcpy(L + i * sizeof(int), array + (left + i) * sizeof(int), sizeof(int));
  }
  for (j = 0; j < n2; j++)
  {
    memcpy(R + j * sizeof(int), array + (mid + 1 + j) * sizeof(int), sizeof(int));
  }
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2)
  {
    if (compare(L + i * sizeof(int), R + j * sizeof(int)) <= 0)
    {
      memcpy(array + k * sizeof(int), L + i * sizeof(int), sizeof(int));
      i++;
    }
    else
    {
      memcpy(array + k * sizeof(int), R + j * sizeof(int), sizeof(int));
      j++;
    }
    k++;
  }
  return array;
}

void *binary_search(void *array, size_t right, size_t k, int (*compare)(const void *, const void *))
{
  size_t left = 0;
  size_t mid = left + (right - left) / 2;
  if(compare(array+mid+sizeof(int),&k)==0)
  {
    return array+mid+sizeof(int);
  } 
  
  else if(compare(array+mid+sizeof(int),&k)<0)
  {
    return binary_search(array,mid+1,k,compare);
  }
  else
  {
    return binary_search(array,mid-1,k,compare);
  }
  return array;
}

void merge_sort(void *array, int left, int right, int (*compare)(const void *, const void *))
{
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
  int j;
  size_t key;
  void* key_loc;
  for(int i = 0;i<right;i++) {
    key_loc = binary_search(array,right,key,compare);
    j=i;
    while(j>right && compare(array+(j-1)*sizeof(int),&key_loc)>0)
    {
      swap(array+(i-1)*sizeof(int),array+i*sizeof(int),sizeof(int));
    }
  }
  
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compare)(const void *, const void *))
{
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
