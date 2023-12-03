#include "common.h"
#include <time.h>


void sort_records(const char *infile, const char *outfile, size_t k, size_t field){
  printf("creating array\n");
  int nitems;
  clock_t start, end;
  FILE *file_in = fopen(infile, "r");
  struct Records *array = create_array(file_in, &nitems);
  fclose(file_in);
  printf("array created without errors\n");
   switch (field)
  {
  case 1:
    start = clock();
    merge_binary_insertion_sort(array, nitems,sizeof(struct Records), k, compare_string);
    end = clock();
    break;
  case 2:
    start  = clock();
    merge_binary_insertion_sort(array, nitems,sizeof(struct Records), k, compare_int);
    end = clock();
    break;
  case 3:
    start = clock();
    merge_binary_insertion_sort(array, nitems,sizeof(struct Records), k, compare_double);
    end = clock();
    break;
  default:
    printf("Invalid field\n");
    exit(EXIT_FAILURE);
  }
  printf("Array sorted in \x1b[35m%lf\x1b[0m  seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

  FILE *f_out = fopen(outfile, "w");
  if(f_out == NULL){
    fprintf(stderr,"Error opening file");
    free(array);
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<nitems;i++){
    fprintf(f_out,"%d,%s,%d,%lf\n",array[i].eId,array[i].field1,array[i].field2,array[i].field3);
  }
  fclose(f_out);
  free(array); 
}

int main(int argc, const char *argv[])
{
  if(argc < 5){
    fprintf(stderr,"Usage: %s <infile> <outfile> <k> <field>\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  size_t k = atoi(argv[3]);
  size_t field = atoi(argv[4]);

  const char *infile = argv[1];
  const char *outfile = argv[2];
 
  sort_records(infile,outfile, k,field);

  return 0;
}