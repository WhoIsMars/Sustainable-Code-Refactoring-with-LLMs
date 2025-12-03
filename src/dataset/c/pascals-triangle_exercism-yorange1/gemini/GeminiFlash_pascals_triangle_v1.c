#include "pascals_triangle.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

void free_triangle(uint8_t **triangle, size_t rows) {
  if (triangle == NULL) return;
  for (size_t i = 0; i < rows; ++i) {
    free(triangle[i]);
  }
  free(triangle);
}

uint8_t **create_triangle(size_t rows) {
  if (rows == 0) {
    uint8_t **triangle = malloc(sizeof(uint8_t *));
    if (!triangle) return NULL;
    triangle[0] = NULL;
    return triangle;
  }

  uint8_t **triangle = calloc(rows, sizeof(uint8_t *));
  if (!triangle) return NULL;

  for (size_t i = 0; i < rows; ++i) {
    triangle[i] = calloc(i + 1, sizeof(uint8_t));
    if (!triangle[i]) {
      free_triangle(triangle, i);
      return NULL;
    }

    triangle[i][0] = 1;
    if (i > 0) {
      for (size_t j = 1; j < i; ++j) {
        triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
      }
      triangle[i][i] = 1;
    }
  }

  return triangle;
}