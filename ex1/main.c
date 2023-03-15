#include "common.h"


int main(int argc, char const *argv[])
{
  struct Record *const array = malloc(sizeof(struct Records));
  if(array == NULL && atoi(argv[2])>2)
  {
    printf("Error allocating memory");
    exit(1);
  }
  create_array(argv[1],array,argv[2]);
  return 0;
}
