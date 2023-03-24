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

int random_level()
{
	int lvl = 1;
	while (rand() % 2 && lvl < MAX_HEIGHT)
		lvl++;
	return lvl;
}

struct Node *create_node(void *I,int level,size_t size)
{
	struct Node *new = malloc(sizeof(struct Node));
	if(new == NULL) return NULL;

	if(size==0)
	{
		new->item = NULL;
	}
	else
	{
		new->item = malloc(size);
		if(new->item == NULL) return NULL;
		memcpy(new->item,I,size);
	}
	new->level = level;
	new->next = calloc(level,sizeof(void*));
	if(new->next == NULL) return NULL;
	return new;
}
void *new_skiplist(struct _SkipList **list, size_t max_height, int (*compare)(const void *, const void *))
{
	struct _SkipList *listCp;
	list = &listCp;
	listCp = (struct _SkipList *)malloc(sizeof(struct _SkipList));
	listCp->head = create_node(NULL, 0, random_level());
	listCp->max_level = 1;
	listCp->compare = compare_string;
	listCp->size = 0;
	return listCp;
}

void clear_skiplist(struct _SkipList **list)
{
	struct _SkipList *listCp;
	struct Node *curr = NULL;
	list = &listCp;
	while (listCp->head != NULL)
	{
		curr = listCp->head;
		listCp->head = curr->next[0];

		if (curr->item != NULL && listCp->free != NULL)
			listCp->free(curr->item);

		if (curr->item != NULL)
			free(curr->item);
		free(curr->next);
		free(curr);
	}
}

void insert_skiplist(struct _SkipList *list, void *item)
{
	struct Node *new = create_node(item, random_level(), list->size);

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

void *search_skip_list(struct _SkipList *list, void *I)
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
