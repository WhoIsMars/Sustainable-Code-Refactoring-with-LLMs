#include <stdlib.h>
#include "pascals_triangle.h"

void free_triangle(uint8_t **triangle, uint8_t rows) {
  if (triangle == NULL) {
    return;
  }
  for (uint8_t i = 0; i < rows; i++) {
    free(triangle[i]);
  }
  free(triangle);
}

uint8_t **create_triangle(uint8_t rows) {
  if (rows == 0) {
    return NULL;
  }

  uint8_t **triangle = (uint8_t **)malloc(rows * sizeof(uint8_t *));
  if (triangle == NULL) {
    return NULL;
  }

  for (uint8_t i = 0; i < rows; i++) {
    triangle[i] = (uint8_t *)malloc((i + 1) * sizeof(uint8_t));
    if (triangle[i] == NULL) {
      // Handle allocation failure: free previously allocated rows
      for (uint8_t j = 0; j < i; j++) {
        free(triangle[j]);
      }
      free(triangle);
      return NULL;
    }

    triangle[i][0] = 1;
    triangle[i][i] = 1;

    for (uint8_t j = 1; j < i; j++) {
      triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
    }
  }

  return triangle;
}