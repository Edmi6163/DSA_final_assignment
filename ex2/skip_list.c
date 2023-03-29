#include "skip_list.h"

int compare_string(const void *a, const void *b)
{
	if (a != NULL && b != NULL)
	{
		char *s1 = *(char **)a;
		char *s2 = *(char **)b;
		return strcmp(s1, s2);
	}
	if (a == NULL && b == NULL)
		return 0;
	if (a == NULL)
		return -1;
	return 1;
}

void free_string(void *a)
{
	free(*(char **)a);
}

int random_level()
{
	int lvl = 1;
	while (rand() % 2 && lvl < MAX_HEIGHT)
		lvl++;
	return lvl;
}

struct Node *create_node(void *I, int level, size_t size)
{
	struct Node *new = malloc(sizeof(struct Node));
	if (new == NULL)
		return NULL;

	if (size == 0)
	{
		new->item = NULL;
	}
	else
	{
		new->item = malloc(size);
		if (new->item == NULL)
			return NULL;
		memcpy(new->item, I, size);
	}
	new->level = level;
	new->next = calloc(level, sizeof(void *));
	if (new->next == NULL)
		return NULL;
	return new;
}

// create a new empty skip list
void new_skiplist(struct _SkipList **list, size_t max_height, int (*compare)(const void *, const void *))
{
	struct _SkipList *new = malloc(sizeof(struct _SkipList));
	if (new == NULL)
	{
		printf("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	new->head = create_node(NULL, max_height, 0);
	if (new->head == NULL)
	{
		printf("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	new->max_level = 1;
	new->size = 0;
	new->compare = compare;
	new->free = NULL;
	*list = new;
}

//delete skip list
void clear_skiplist(struct _SkipList **list)
{
	struct Node *x = (*list)->head;
	struct Node *y = NULL;
	while (x != NULL)
	{
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

void insert_skiplist(struct _SkipList *list, void *item)
{
	struct Node *new = create_node(item, random_level(list), list->size);

	if (new == NULL)
	{
		printf("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	if (new->level > list->max_level)
		list->max_level = new->level;

	struct Node *x = list->head;

	for (int k = list->max_level - 1; k >= 0;)
	{
		if (x->next[k] == NULL || (list->compare(item, x->next[k]->item) < 0))
		{
			if (k < new->level)
			{
				new->next[k] = x->next[k];
				x->next[k] = x->next[k];
				printf("inserting %s\n", *(char **)x->next[k]->item);
			}
			k--;
		}
		else
		{
			x = x->next[k];
		}
	}
}

const void *search_skip_list(struct _SkipList *list, void *I)
{
	struct Node *x = list->head;

	for (int i = list->max_level - 1; i >= 0; i--)
	{
		while (x->next[i] != NULL && list->compare(x->next[i]->item, I) < 0)
		{
			x = x->next[i];
		}
	}

	x = x->next[0];

	if (x == NULL || list->compare(x->item, I) != 0)
		return NULL;
	else
		return x->item;
}

struct _SkipList *create_skiplist(int (*compare)(const void *, const void *), void (*free)(void *), size_t size)
{
	struct _SkipList *new = malloc(sizeof(struct _SkipList));
	if (new == NULL)
		return NULL;

	struct Node *sentinel = create_node(NULL, MAX_HEIGHT, 0);
	if (sentinel == NULL)
		return NULL;
	new->head = sentinel;
	new->free = free;
	new->compare = compare;
	new->max_level = 1;
	new->size = size;
	return new;
}
