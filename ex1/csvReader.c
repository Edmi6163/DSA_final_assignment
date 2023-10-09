#include "common.h"
#include <stddef.h>
#include <stdio.h>

size_t n_row(const char *file_path) {
  FILE *fp = fopen(file_path, "r");
  char buffer[BUFF_SIZE];
  size_t nRow = 0;

  while (fgets(buffer, BUFF_SIZE, fp))
    nRow++;
  fclose(fp);
  return nRow;
}

struct Records *create_array(const char *file_path, struct Records *array,
                             size_t size) {
  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    perror("Error opening file");
    return NULL;
  }

  size_t numRecords = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      numRecords++;
    }
  }
  fseek(file, 0, SEEK_SET);

  struct Records *records =
      (struct Records *)malloc(numRecords * sizeof(struct Records));
  if (records == NULL) {
    perror("Error allocating memory");
    fclose(file);
    return NULL;
  }

  char line[256];
  int recordIndex = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (sscanf(line, "%d,%[^,],%d,%lf", &records[recordIndex].eId, line,
               &records[recordIndex].field2,
               &records[recordIndex].field3) == 4) {
      records[recordIndex].field1 = strdup(line);
      // printf("Read eId: %d, field1: %s, field2: %d, field3: %.2lf\n",records[recordIndex].eId, records[recordIndex].field1,records[recordIndex].field2, records[recordIndex].field3);
      recordIndex++;
    } else {
      printf("Error parsing line: %s\n", line);
    }
  }

  fclose(file);
  size = numRecords;
  return records;
}
