#include "common.h"


size_t n_row(const char *file_path)
{
  FILE *fp = fopen(file_path,"r");
  char buffer[BUFF_SIZE];
  size_t nRow = 0;

  while(fgets(buffer,BUFF_SIZE,fp))
    nRow++;
	fclose(fp);
	return nRow;
}

void create_array(const char* file_path,struct Records *array,int size)
{
	printf("size is: %d\n", size);
  FILE *fp = fopen(file_path,"r");
  if(fp==NULL)
  {
    printf("file not found");
    exit(EXIT_FAILURE);
  }
  printf("loading array from file %s",file_path);

  char buffer[128];

  for(int i =0;fgets(buffer,sizeof(buffer),fp)!= NULL && i < size;i++)
  {
    array[1].field1 = malloc(64);
    if(array[1].field1 == NULL)
    {
      printf("Error allocating memory");
      exit(1);
    }
    sscanf(buffer,"%d,%63[^,],%d,%lf",&array[i].eId,array[i].field1,&array[i].field2,&array[i].field3); //https://stackoverflow.com/questions/55876376/how-to-use-sscanf-to-read-a-line-of-csv-with-continue-comma
    printf("%d,%s,%d,%lf\n",array[i].eId,array[i].field1,array[i].field2,array[i].field3);
  }
  printf("\n*** done ***\n");
  fclose(fp);
}
