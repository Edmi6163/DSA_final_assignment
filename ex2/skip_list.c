#include "skip_list.h"

int random_level()
{
	int lvl = 1;
	while(rand() %2 && lvl < MAX_HEIGHT) lvl++;
	return lvl;
}

void new_skiplist(struct _SkipList **list, size_t max_height, int (*compare)(const void *, const void *))
{
}

void clear_skiplist(struct _SkipList **list)
{
	struct _SkipList *listCp;
	struct Node *curr = NULL;
	list = &listCp;
	while(listCp->head != NULL)
	{
		curr = listCp->head;
		listCp->head = curr->next[0];

		if(curr->item != NULL && listCp->free != NULL)
			listCp->free(curr->item);

		if(curr->item != NULL)
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

	for(int k =list->max_level -1;k>=0; )
	{
		if(x->next[k]==NULL || (list->compare(item,x->next[k]->item )<0))
		{
			if(k<new->level)
			{
				new->next[k] = x->next[k];
				x->next[k] = x->next[k];
				printf("inserting %s\n",*(char**)x->next[k]->item); 
			}
			k--;
		} 
		else 
		{
			x = x->next[k];
		}
	}
}


void *search_skip_list(struct _SkipList *list,void *I)
{
	struct Node *x = list->head;

	for(int i =list->max_level -1;i>=0; i--)
	{
		while(x->next[i] != NULL && list->compare(x->next[i]->item,I)<0)
		{
			x = x->next[i];
		}
	}

	x= x->next[0];

	if(x==NULL || list->compare(x->item,I)!= 0)
		return NULL;
	else 
		return x->item;
}