#pragma once
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUFF_SIZE 1024

struct Records
{
  int eId;
  char *field1;
  int field2;
  double field3;
};

struct Records *create_array(const char* file_path,struct Records *array,size_t size);
size_t n_row(const char *file_path);
void merge_binary_insertion_sort(void *base,size_t nitems,size_t size,size_t k,int (*compare)(const void*,const void *));
void merge(void *array,int left,int mid,int right,size_t size,int (*compare)(const void *,const void *));

int compare_string(const void *a, const void *b);
int compare_int(const void *a, const void *b);
int compare_double(const void *a, const void *b);
