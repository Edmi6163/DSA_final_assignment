#include "skip_list.h"

#define MAXC 256
#define MAX_HEIGHT 16 


void to_lowercase(char *str){
  for(int i = 0; str[i]; i++){
    str[i] = tolower(str[i]);
  }
}
void reading_dictionary(const char *dictfile, struct _SkipList *list) {

  char buffer[MAXC];
  FILE *fp = fopen(dictfile, "r");

  printf("Loading dictionary from file \x1b[33m%s\n\x1b[0m", dictfile);
  TEST_ERROR

  while (fgets(buffer, sizeof(buffer), fp)) {
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

 
  fclose(fp);
}

void find_errors(const char *dictfile, const char *textfile) {
  struct _SkipList *list;
  clock_t begin, end;
	FILE *phrase = fopen(textfile,"r");
  new_skiplist(&list, MAX_HEIGHT, compare_string);
  reading_dictionary(dictfile, list);

	char line[1024];

  printf("looking for any errors .... \n");
	while(fgets(line,sizeof(line),phrase)){
		char *token = strtok(line," \t\n\r.,;:!-");
		while(token){
      to_lowercase(token); 
      begin = clock();
			if(!search_skip_list(list,token)){
      printf("The word \033[31m%s\033[0m was not found, so probably is written incorrectly\n",token);
			}
      end = clock();
			token = strtok(NULL, " \t\n\r.,;:!-");
		}

    printf("Time taken: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
		fclose(phrase);
		clear_skiplist(&list);
	}

}

int main(int argc, char **argv) {
  const char *dict = argv[1];
  const char *corr = argv[2];

  printf(":::>dict path %s<::: \n", dict);
  printf(":::>corr path %s<::: \n", corr);

  if (argc < 3)
    printf("not enough argument passed \n");
  TEST_ERROR
  find_errors(dict, corr);
  return 0;
}
