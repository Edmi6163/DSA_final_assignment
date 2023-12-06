#include "skip_list.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXC 256


void to_lowercase(char *str){
  for(int i = 0; str[i]; i++){
    str[i] = tolower(str[i]);
  }
}

void reading_dictionary(FILE *dictfile, struct SkipList *list) {

  char buffer[MAXC];

  printf("Loading dictionary from file dictionary file\n");
  TEST_ERROR

  while (fgets(buffer, sizeof(buffer), dictfile)) {
    strtok(buffer, "\n");
    to_lowercase(buffer);
    char *word_to_insert = malloc(strlen(buffer) + 1);
    strcpy(word_to_insert, buffer);
    if (!word_to_insert) {
      fprintf(stderr,"Error allocating memory\n");
      exit(1);
    }
    insert_skiplist(list, word_to_insert);
  }
	printf("dictionary loaded\n");
}

void find_errors(FILE *dictfile,FILE *textfile,size_t max_height) {
  struct SkipList *list;
  clock_t begin, end;
	char line[1024];
  new_skiplist(&list, max_height, compare_string);
  reading_dictionary(dictfile, list);


  printf("looking for any errors .... \n");
	while(fgets(line,sizeof(line),textfile)){
		char *token = strtok(line," \t\n\r.,;:!-");
		while(token){
      to_lowercase(token); 
      begin = clock();
			if(!search_skiplist(list,token)){
      printf("The word \033[31m%s\033[0m was not found, so probably is written incorrectly\n",token);
			}
      end = clock();
			token = strtok(NULL, " \t\n\r.,;:!-");
		}

    printf("\x1b[33mTime taken with max_height %zu is: %f seconds\n\x1b[0m\n",max_height, (double)(end - begin) / CLOCKS_PER_SEC);
		fclose(textfile);
		clear_skiplist(&list);
	}
}

int main(int argc, char **argv) {
  const char *dict = argv[1];
  const char *corr = argv[2];

  size_t max_height = strtoul(argv[3], NULL, 10);

  printf(":::> dict path %s <::: \n", dict);
  printf(":::> corr path %s <::: \n", corr);
  FILE *dictionary = fopen(dict, "r");
  FILE *to_correct = fopen(corr, "r");

  if (argc < 4)
    printf("not enough argument passed \n");
  TEST_ERROR
  find_errors(dictionary, to_correct,max_height);
  return 0;
}
