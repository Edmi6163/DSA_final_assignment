#include "skip_list.h"

#define MAXW 64 // usually a words isn't longer than 64 characters
#define MAXC 256

int get_phrase(const char *file_name, char *arr[64])
{
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}

	printf("Loading array from file \033[1m%s\033[22m \0337\033[5m...\n", file_name);

	bool cont = false;
	char c;
	int words = 0, chars = 0;

	arr[words] = calloc(MAXW, sizeof(char)); // first word needs to be manually alloc'd
	if (arr[words] == NULL && MAXW > 0)
	{
		printf("Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	while (((c = fgetc(fp)) != EOF) && words < MAXW)
	{
		if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		{
			if (!cont)
				continue; // makes fgetc loop until it finds a letter

			arr[words][chars] = '\0';
			chars = 0;
			arr[++words] = calloc(MAXW, sizeof(char));
			if (arr[words] == NULL && MAXW > 0)
			{
				printf("Error allocating memory\n");
				exit(EXIT_FAILURE);
			}
			cont = false;
		}
		else
		{
			if (c >= 'A' && c <= 'Z')
				c += 32; // lowercase
			arr[words][chars++] = c;
			cont = true;
		}
	}
	printf("\033[25m\0338\033[32mdone\033[0m\n");

	if (!cont)
		free(arr[words--]); // fixes case in which while loop thinks there's a word to be read but there's only random chars

	fclose(fp);
	return words;
}

void reading_dictionary(const char *dictfile, struct _SkipList *list)
{

	char buffer[128];
	int words_count = 0;
	FILE *fp = fopen(dictfile, "r");

	printf("Loading dictionary from file \x1b[33m%s\n\x1b[0m", dictfile);
	TEST_ERROR

	for (int i = 0; fgets(buffer, sizeof(buffer), fp) != NULL; i++)
	{
		char *word = calloc(MAXW, sizeof(char));
		if (word == NULL && MAXW > 0)
		{
			printf("Error allocating memory \n");
			exit(EXIT_FAILURE);
		}
		sscanf(buffer, "%s", word);
		insert_skiplist(list, word);
		words_count++;
	}
	printf("\n completed dictionary \n");
	fclose(fp);
}

void find_errors(const char *dictfile, const char *textfile, size_t max_height)
{
	struct _SkipList *list = NULL;
	new_skiplist(&list, 10, compare_string);
	printf("reading dictionary from file  %s\n", dictfile);
	reading_dictionary(dictfile, list);
	char *phrase[MAXW] = {0};
	int words = get_phrase(textfile, phrase);
	printf("words amount is %d\n", words);

	for (int i = 0; i < words; i++)
	{
		printf("checking word %s\n", phrase[i]);
		if (search_skip_list(list, &phrase[i]) == NULL)
			printf("%s ", phrase[i]);
	}

	clear_skiplist(&list);
	printf("\n");
}

int main(int argc, char **argv)
{
	const char *dict = argv[1];
	const char *corr = argv[2];

	printf(":::>dict path %s<::: \n", dict);
	printf(":::>corr path %s<::: \n", corr);

	if (argc < 3)
		printf("not enough argument passed \n");
	TEST_ERROR
	find_errors(dict, corr, 10);
	printf("looking for any errors .... \n");
	return 0;
}
