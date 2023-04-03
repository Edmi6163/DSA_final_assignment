#include "common.h"

int main(int argc, const char *argv[])
{
  int size = n_row(argv[1]);
  struct Records *array = calloc(size, sizeof(struct Records));
  if (array == NULL)
  {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }
  printf("creating array\n");
  create_array(argv[1], array, size);
  //question for the user

  return 0;
}
