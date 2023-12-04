#pragma once
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



struct Node {
  struct Node **next;
  size_t size;
  void *item;
};

struct _SkipList {
  struct Node **head;
  size_t max_level;
  size_t max_height;
  int (*compare)(const void*,const void*);
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

//method prototypes
const void *search_skip_list(struct _SkipList *list, void *item);
void insert_skiplist(struct _SkipList *list,void *item);
void clear_skiplist(struct _SkipList **list);
int compare_string(const void* a, const void* b);
void free_string(void *a);
void new_skiplist(struct _SkipList **list, size_t max_height, int (*compare)(const void *, const void *));
