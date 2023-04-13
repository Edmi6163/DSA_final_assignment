#include "common.h"

int main(int argc, const char *argv[])
{

  int k;
  int field;
  size_t nitems = n_row(argv[1]);
  
  struct Records *array = calloc(nitems, sizeof(struct Records));
  if (array == NULL)
  {
    fprintf(stderr,"Error allocating memory");
    exit(EXIT_FAILURE);
  }
  printf("creating array\n");
  create_array(argv[1], array, nitems);
  // question for the user, of how much k is
  printf("Which value would u like to use for k?: ");
  scanf("%d", &k);
  // wich field to sort
  printf("Which field would u like to sort?\n:1 field1\n:2 field2\n:3 field3\n ");
  scanf("%d", &field);
  //sizeof() in bytes of each element in the array
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

  return 0;
}
