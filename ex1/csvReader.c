#include "common.h"
#include <stdio.h>

void free_row(struct Records *line) { free(line->field1); }
bool is_number(const char *str) {
  // Ignore leading whitespace
  while (*str && isspace(*str)) {
    str++;
  }

  // Check for a sign (+ or -)
  if (*str == '+' || *str == '-') {
    str++;
  }

  bool has_decimal_point = false;
  bool has_digit = false;
  while (*str) {
    if (*str == '.') {
      if (has_decimal_point) {
        return false; // Multiple decimal points are not allowed
      }
      has_decimal_point = true;
    } else if (isdigit(*str)) {
      has_digit = true;
    } else {
      return false; // Non-digit characters are not allowed
    }
    str++;
  }

  return has_digit; // Ensure there is at least one digit in the number
}

/*
 * Reads the file and creates an array of Records
 * Returns NULL if there was an error
 * memory gets reallocated if needed
 */
struct Records *create_array(FILE *fp, int *num_rows) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read_bytes;
  int num_allocated = 32;
  int num_read = 0;
  struct Records *rows = malloc(num_allocated * sizeof(struct Records));
  if (rows == NULL) {
    fprintf(stderr,"Error allocating memory for rows");
    return NULL;
  }

  if (fp == NULL) {
    fprintf(stderr,"Error opening file");
    free(rows);
    return NULL;
  }

  while ((read_bytes = getline(&line, &len, fp)) != -1) {
    if (line[read_bytes - 1] == '\n') {
      line[read_bytes - 1] = '\0';
    }

    if (num_read >= num_allocated) {
      num_allocated *= 2;
      struct Records *new_rows =
          realloc(rows, num_allocated * sizeof(struct Records));
      if (new_rows == NULL) {
        fprintf(stderr,"Error reallocating memory for rows");
        for (int i = 0; i < num_read; i++) {
          free_row(&rows[i]);
        }
        free(rows);
        fclose(fp);
        free(line);
        return NULL;
      }
      rows = new_rows;
    }

    char *token;
    char *next_ptr;
    int field = 0;

    token = strtok_r(line, ",", &next_ptr);
    while (token != NULL) {
      switch (field) {
      case 0:
        if (!is_number(token)) {
          fprintf(stderr, "Error parsing ID field\n");
          goto next_line;
        }
        rows[num_read].eId = atoi(token);
        break;
      case 1:
        rows[num_read].field1 = strdup(token);
        if (rows[num_read].field1 == NULL) {
          fprintf(stderr,"Error allocating memory for field1\n");
          for (int i = 0; i < num_read; i++) {
            free_row(&rows[i]);
          }
          free(rows);
          fclose(fp);
          free(line);
          return NULL;
        }
        break;
      case 2:
        if (!is_number(token)) {
          fprintf(stderr, "Error parsing field2\n");
          goto next_line;
        }
        rows[num_read].field2 = atoi(token);
        break;
      case 3:
        if (!is_number(token)) {
          fprintf(stderr, "Error parsing field3\n");
          goto next_line;
        }
        rows[num_read].field3 = strtod(token, NULL);
        break;
      default:
        fprintf(stderr, "Error: too many fields in the row\n");
        goto next_line;
      }
      field++;
      token = strtok_r(NULL, ",", &next_ptr);
    }

    if (field != 4) {
      fprintf(stderr, "Error: not enough fields in the row\n");
      goto next_line;
    }

    num_read++;

  next_line:
    continue;
  }

  fclose(fp);
  if (line)
    free(line);

  *num_rows = num_read;
  return rows;
}
