#include "common.h"
#include <stdio.h>


  // exc 0 file in 1 file out 2 k 3 field 4
int main(int argc, const char *argv[])
{

  int field;
  int k = atoi(argv[3]);
  size_t nitems = n_row(argv[1]);

  
  struct Records *array = calloc(nitems, sizeof(struct Records));
  if (array == NULL)
  {
    fprintf(stderr,"Error allocating memory");
    exit(EXIT_FAILURE);
  }
  printf("creating array\n");
  create_array(argv[1], array, nitems);
  switch (atoi(argv[4]))
  {
  case 1:
    merge_binary_insertion_sort(array, nitems,sizeof(struct Records), k, compare_string);
    break;
  case 2:
    merge_binary_insertion_sort(array, nitems,sizeof(struct Records), k, compare_int);
    break;
  case 3:
    merge_binary_insertion_sort(array, nitems,sizeof(struct Records), k, compare_double);
    break;
  default:
    printf("Invalid field\n");
    exit(EXIT_FAILURE);
  }

  FILE *f_out = fopen(argv[2], "w");
  if(f_out == NULL){
    fprintf(stderr,"Error opening file");
    free(array);
    exit(EXIT_FAILURE);
  }
  for(size_t i=0;i<nitems;i++){
    fprintf(f_out,"%d,%s,%d,%lf\n",array[i].eId,array[i].field1,array[i].field2,array[i].field3);
  }
  fclose(f_out);
  free(array);
  return 0;
}
