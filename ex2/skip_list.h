#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


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
