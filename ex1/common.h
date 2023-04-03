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
void insertion_sort(void *array,size_t size);
void merge_sort(void *array,int left,int k);