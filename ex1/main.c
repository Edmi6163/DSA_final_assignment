#include "common.h"


void sort_records(const char *infile, const char *outfile, size_t k, size_t field){
  printf("creating array\n");
  int nitems;
  FILE *file_in = fopen(infile, "r");
  struct Records *array = create_array(file_in, &nitems);
  printf("array created without errors\n");
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
  fclose(file_in);
  free(array); 
}

  // TODO remove this exc 0 file in 1 file out 2 k 3 field 4
int main(int argc, const char *argv[])
{

  size_t k = atoi(argv[3]);
  size_t field = atoi(argv[4]);

  const char *infile = argv[1];
  const char *outfile = argv[2];
 
  FILE *file_in = fopen(infile, "r");
  sort_records(infile,outfile, k,field);

  return 0;
}
