#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>

#define MAX_HEIGHT 20
struct Node {
  struct Node **next;
  size_t size;
  int level;
  void *item;
};

struct _SkipList {
  struct Node *head;
  size_t max_level;
  size_t size;
  size_t max_height;
  int (*compare)(const void*,const void*);
  void (*free)(void *); // free function for the elements in the list
};

//method prototypes
const void *search_skip_list(struct _SkipList *list, void *I);
struct _SkipList *create_skiplsit(int (*compare)(const void *,const void *), void (*free)(void *),size_t size);
void insert_skiplist(struct _SkipList *list,void *item);
void clear_skiplist(struct _SkipList **list);
int compare_string(const void* a, const void* b);
void free_string(void *a);