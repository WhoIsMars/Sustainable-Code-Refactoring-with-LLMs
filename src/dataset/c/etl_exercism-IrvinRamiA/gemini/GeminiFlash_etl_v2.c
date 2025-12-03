#include "etl.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

static int compare(const void *a, const void *b) {
  return ((new_map *)a)->key - ((new_map *)b)->key;
}

int convert(const legacy_map *input, const size_t input_len, new_map **output) {
  size_t output_length = 0;
  size_t output_index = 0;

  // Calculate output length efficiently, avoiding repeated strlen calls.
  for (size_t i = 0; i < input_len; ++i) {
    output_length += strlen(input[i].keys);
  }

  // Allocate memory for the output map.  Check for allocation failure.
  *output = (new_map *)malloc(output_length * sizeof(new_map));
  if (*output == NULL) {
    return -1; // Indicate memory allocation failure.
  }

  // Populate the output map.
  for (size_t i = 0; i < input_len; ++i) {
    const char *keys = input[i].keys;
    unsigned char value = input[i].value;
    for (size_t j = 0; keys[j] != '\0'; ++j) {
      (*output)[output_index].key = tolower(keys[j]);
      (*output)[output_index].value = value;
      output_index++;
    }
  }

  // Sort the output map.
  qsort(*output, output_length, sizeof(new_map), compare);

  return (int)output_length;
}