#include "skip_list.h"

#define MAXW 64 // usually a words isn't longer than 64 characters
#define MAXC 256

FILE *fp, *fp1;

// int get_phrase(char *phrase[], FILE *fp1)
int get_phrase(char *phrase[], const char *phrasefile)
{
	bool con = false;
	char c;
	int words = 0, chars = 0;

	phrase[words] = calloc(MAXW, sizeof(char)); // first word need to be manually allocated
	if (phrase[words] == NULL && MAXW > 0)
	{
		printf("Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	while (((c = fgetc(fp1) != EOF) && words < MAXW))
	{
		if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		{
			if (!con)
				continue; // makes fgetc loop until it finds a letter
			phrase[words][chars] = '\0';
			chars = 0;
			phrase[++words] = calloc(MAXW, sizeof(char));
			if (phrase[words] == NULL && MAXW > 0)
			{
				printf("Error allocating memory\n");
				exit(EXIT_FAILURE);
			}
			con = false;
		}
		else
		{
			if (c > 'A' && c <= 'Z')
				c += 32;
			phrase[words][chars++] = c;
			con = true;
		}
	}
	return words;
}

// void reading_dictionary(FILE *fp, struct _SkipList *list)
void reading_dictionary(const char *dictfile, struct _SkipList *list)
{
	printf("Loading dictionary from file \033[1m%s\033[22m\0337\033[5m", dictfile);
	char buffer[128];
	int words_count = 0;

	for (int i = 0; fgets(buffer, sizeof(buffer), fp) != NULL; i++)
	{
		char *word = calloc(MAXW, sizeof(char));
		if (word == NULL && MAXW > 0)
		{
			printf("Error allocating memory \n");
			exit(EXIT_FAILURE);
		}
		sscanf(buffer, "%s", word);
		insert_skiplist(list, &word);
		words_count++;
	}

	printf("\n completed dictionary \n");
}
void find_errors(const char *dictfile, const char *textfile, const size_t max_height)
{
	struct _SkipList *list = create_skiplist(compare_string, free_string, sizeof(char *));
	reading_dictionary(dictfile, list);
	char *phrase[MAXW];
	int words = get_phrase(phrase, textfile);
	for (int i = 0; i < words; i++)
	{
		if (search_skip_list(list, &phrase[i]) == NULL)
			printf("%s ", phrase[i]);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	// printf("argv 1 is: %s\n ", argv[1]);
	// printf("argv 2 is: %s\n ", argv[2]);
	const char *dict = "input/dictionary.txt";
	const char *corr = "input/correctme.txt";
	struct _SkipList *list = create_skiplist(compare_string, free_string, sizeof(char *));

	printf(":::dict path %s::: \n", dict); // TODO this need to be the arguments
	printf(":::corr path %s::: \n", corr);
	printf("opening files.... \n");
	fp = fopen(dict, "r");
	fp1 = fopen(corr, "r"); // TODO change with argv[1] and argv[2]
	// if (argc < 3)
	// printf("not enough argument passed \n");

	if (!fp && !fp1)
	{
		printf("can't open file \n");
		TEST_ERROR
		exit(1);
	}
	printf("reading dictionary.....\n");
	TEST_ERROR
	//	reading_dictionary(fp, list); // FIXME here segfault
	find_errors(dict, corr, list->max_height);
	printf("\n----------------\n");
	printf("\n----------------\n");

	fclose(fp);
	fclose(fp1);
	clear_skiplist(&list);
	return 0;
}
