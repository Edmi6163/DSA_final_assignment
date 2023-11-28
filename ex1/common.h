#pragma once
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFF_SIZE 1024

struct Records
{
  int eId;
  char *field1;
  int field2;
  double field3;
};

#ifndef TEST_ERROR
#define TEST_ERROR                                 \
    if (errno)                                     \
    {                                              \
        fprintf(stderr,                            \
                "%s:%d: PID=%5d: Error %d (%s)\n", \
                __FILE__,                          \
                __LINE__,                          \
                getpid(),                          \
                errno,                             \
                strerror(errno));                  \
    }
#endif

struct Records *create_array(FILE *fp,int *num_rows);
size_t n_row(const char *file_path);
void merge_binary_insertion_sort(void *base,size_t nitems,size_t size,size_t k,int (*compare)(const void*,const void *));
void merge(void *array,size_t mid,size_t right,size_t size,int (*compare)(const void *, const void *));

int compare_string(const void *a, const void *b);
int compare_int(const void *a, const void *b);
int compare_double(const void *a, const void *b);
