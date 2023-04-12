#pragma once
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

struct Records
{
  int eId;
  char *field1;
  int field2;
  double field3;
};

void create_array(const char* file_path,struct Records *array,int size);
int n_row(const char *file_path);
void merge_binary_insertion_sort(void *base,size_t nitems,size_t size,size_t k,int (*compare)(const void*,const void *));
void binary_insertion_sort(void *array,int left,int right,int (*compare)(const void*,const void *));

int compare_string(const void *a, const void *b);
int compare_int(const void *a, const void *b);
int compare_double(const void *a, const void *b);
