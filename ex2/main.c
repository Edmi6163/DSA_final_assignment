#include "skip_list.h"

#define MAXW 64 // usually a words isn't longer than 64 characters
#define MAXC 256

int get_phrase(char *phrase[], FILE *fp1)
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
		if (c < 'A' || (c > 'Z' && c < 'a' )|| c > 'z')
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

void find_errors(const char *dictfile, const char *textfile,const size_t max_height,struct _SkipList *list)
{

	char *phrase[MAXC] = {0};
	printf("\n reading phrase \n");

	int words = get_phrase(phrase, textfile);

	for (int j = 0; j < words; j++)
	{
		printf("%s\n", phrase[j]);
	}

	printf("\n----------------\n");
	printf("\n----------------\n");

	clock_t time_start = clock();

	printf("clock start: %ld\n", time_start);

	for (int i = 0; i < words; i++)
	{
		if (search_skip_list(list, &phrase[i]) == NULL)
			printf("\e[0;34mNot found in disctionary: %s\n\e[0m", phrase[i]);
	}

	clock_t time_end = clock();
	double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
	printf("\e[0;33mtime spent with max_height value: %f\n\e[0m", time_spent);
}

void reading_dictionary(FILE *fp, struct _SkipList *list)
{
	printf("Loading dictionary from file \033[1m%s\033[22m\0337\033[5m", fp);
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
}

int main(int argc, char **argv)
{
	printf("argv 1 is: %s\n ", argv[1]);
	printf("argv 2 is: %s\n ", argv[2]);
	FILE *fp, *fp1;

	struct _SkipList *list = create_skiplist(compare_string, free_string, sizeof(char *));
	printf("opening files.... \n");
	fp = fopen(argv[1], "r");
	fp1 = fopen(argv[2], "r");

	if (&argv[1] < 2)
		printf("not enough argument passed \n");

	if (!fp && !fp1)
	{
		printf("can't open file \n");
		printf("error: %s\n", strerror(errno));
		exit(1);
	}
	printf("reading dictionary.....\n");
	reading_dictionary(fp, list);
	printf("\n completed dictionary \n");
	printf("\n----------------\n");
	printf("\n----------------\n");

	find_errors(fp, fp1, list->max_height,list);
	fclose(fp);
	fclose(fp1);
	clear_skiplist(&list);
	return 0;
}
