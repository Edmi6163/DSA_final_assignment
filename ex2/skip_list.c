#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_string(const void *a, const void *b) {
  return strcmp((char *)a, (char *)b);
}

void free_string(void *a) {
  printf("string to free: %s", (char *)a);
  free((char *)a);
}

int random_level(void) {
  int lvl = 1;
  while (rand() % 2 && lvl < MAX_HEIGHT)
    lvl++;
  return lvl;
}

struct Node *create_node(void *I, int level, size_t size) {
  struct Node *new = (struct Node *)malloc(sizeof(struct Node));
  printf("creating node with level %d\n", level);
  if (new == NULL) { 
    fprintf(stderr,"%s %s Error allocating memory",__func__,__FILE__);
    return NULL;
  }
  printf("%s %s %d size:%zu\n",__func__,__FILE__,__LINE__,size);
  if (size == 0) {
    fprintf(stderr,"%s %s %d size == 0 \n",__func__,__FILE__,__LINE__);
    new->item = NULL;
  } else {
    new->item = malloc(size);
    if (new->item == NULL) {
      fprintf(stderr,"%s %s new->item is NULL",__func__,__FILE__);
      free(new);
      return NULL;
    }
    memcpy(new->item, I, size);
  }
  new->level = level;
  new->next = calloc(level, sizeof(void *));
  if (new->next == NULL) {
    fprintf(stderr,"%s %s new->next is NULL",__func__,__FILE__);
    free(new->item);
    free(new);
    return NULL;
  }
  return new;
}

/*
 create a new empty skip list
*/
void new_skiplist(struct _SkipList **list, size_t max_height,
                  int (*compare)(const void *, const void *)) {
  struct _SkipList *new = malloc(sizeof(struct _SkipList));
  if (new == NULL) {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }
  new->head = create_node(NULL, max_height, 0);
  if (new->head == NULL) {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }
  new->max_level = random_level();
  new->size = 0;
  new->compare = compare;
  new->free = NULL;
  *list = new;
}

/*
 delete skip list
 */
void clear_skiplist(struct _SkipList **list) {
  struct Node *x = (*list)->head;
  struct Node *y = NULL;
  while (x != NULL) {
    y = x->next[0];
    if ((*list)->free != NULL)
      (*list)->free(x->item);
    free(x->next);
    free(x);
    x = y;
  }
  free(*list);
  *list = NULL;
}

/*
  insert item in skip list
*/

void insert_skiplist(struct _SkipList *list, void *item) {
  assert(list != NULL);
  if(item == NULL){
    fprintf(stderr,"%s %s %d item is NULL\n",__func__,__FILE__,__LINE__);
    return;
  }
  int level = random_level();
  fprintf(stderr,"%s %s %d %ld\n",__func__,__FILE__,__LINE__,strlen((char *)item));

  struct Node *new = create_node(item, level, strlen((char *)item));

  
  printf("new node created with level %d\n", new->level);
  printf("list->max_level %ld\n", list->max_level);

  if (new == NULL) {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  if (new->level > list->max_level)
    list->max_level = new->level;

  struct Node *x = list->head; //FIXME x->item is NULL 
  printf("x points to %p\n", (void *) x);
  fflush(stdout);
  if(list == NULL) {
    printf("list is null\n");
    return;
  }
  for (size_t k = list->max_level-1; k >= 1; k--) {
    /*while (x->next[k] != NULL && list != NULL && list->compare(item, x->next[k]->item) < 0) {
      x = x->next[k]; //TODO x->next[k] enter in second loop NULL
    } */
    if(x->next[k] != NULL)
    if(x->next[k]==NULL||(*(list)->compare)(item, (x->next[k])->item)) {
      if (k <= level) {
        if(x==NULL){
          fprintf(stderr,"x is null");
          return;
        }
        new->next[k] = x->next[k];
        x->next[k] = new;
      }else{
        x = x -> next[k];
        k++;
      }
    }
  }
  //printf("[%s] inserted %s at level %d\n",__FILE__, (char *)new->item,level);
}

/*
  search item in skip list
*/
const void *search_skip_list(struct _SkipList *list, void *I) {
  struct Node *x = list->head;
  for (int i = list->max_level - 1; i >= 0; i--) {
    while (x->next[i] != NULL && list->compare(x->next[i]->item, I) < 0) {
      printf("x->next[i] %s\n", *(char **)x->next[i]->item);
      x = x->next[i];
    }
  }

  x = x->next[0];

  if (x == NULL || list->compare(x->item, I) != 0)
    return NULL;
  else
    return x->item;
}
