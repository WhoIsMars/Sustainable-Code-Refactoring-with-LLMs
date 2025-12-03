#include "etl.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_NUM (26)

int convert(const legacy_map *input, const size_t input_len, new_map **output) {
  size_t count = 0;
  int map_table[ALPHA_NUM] = {0};

  // First pass: Populate the map_table
  for (size_t i = 0; i < input_len; ++i) {
    const char *keys = input[i].keys;
    for (const char *key = keys; *key != '\0'; ++key) {
      int index = tolower(*key) - 'a';
      if (index >= 0 && index < ALPHA_NUM && map_table[index] == 0) {
        map_table[index] = input[i].value;
        count++;
      }
    }
  }

  // Allocate memory only once, based on the actual number of mappings.
  *output = (new_map *)malloc(count * sizeof(new_map));
  if (*output == NULL) {
    return -1; // Indicate memory allocation failure
  }

  size_t output_index = 0;
  for (int i = 0; i < ALPHA_NUM; ++i) {
    if (map_table[i] != 0) {
      (*output)[output_index].key = 'a' + i;
      (*output)[output_index].value = map_table[i];
      output_index++;
    }
  }

  return output_index;
}