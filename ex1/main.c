#include "common.h"
#include <stdio.h>


void sort_records(const char *infile, const char *outfile, size_t k, size_t field){
  size_t nitems = n_row(infile);
  struct Records *array = calloc(nitems, sizeof(struct Records));
  if (array == NULL)
  {
    fprintf(stderr,"Error allocating memory");
    exit(EXIT_FAILURE);
  }
  printf("creating array\n");
  create_array(infile, array, nitems);
  printf("array created withour errors\n");
   switch (field)
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

  FILE *f_out = fopen(outfile, "w");
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
}

  // TODO remove this exc 0 file in 1 file out 2 k 3 field 4
int main(int argc, const char *argv[])
{

  size_t k = atoi(argv[3]);
  size_t field = atoi(argv[4]);

  const char *infile = argv[1];
  const char *outfile = argv[2];
 
  sort_records(infile,outfile, k,field);

  return 0;
}
