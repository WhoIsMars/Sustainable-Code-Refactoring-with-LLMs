#include "saddle_points.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

saddle_points_t *saddle_points(uint8_t rows, uint8_t cols, uint8_t matrix[rows][cols]) {
  saddle_points_t *result = (saddle_points_t *)malloc(sizeof(saddle_points_t));
  if (!result) return NULL;

  result->points = NULL;
  result->count = 0;

  if (rows == 0 || cols == 0) return result;

  saddle_point_t *points = (saddle_point_t *)malloc(rows * cols * sizeof(saddle_point_t));
  if (!points) {
      free(result);
      return NULL;
  }

  uint8_t total_saddle_points = 0;

  for (uint8_t i = 0; i < rows; i++) {
    for (uint8_t j = 0; j < cols; j++) {
      bool is_saddle = true;

      // Check if it's the largest in its row
      for (uint8_t k = 0; k < cols; k++) {
        if (matrix[i][j] < matrix[i][k]) {
          is_saddle = false;
          break;
        }
      }

      if (is_saddle) {
        // Check if it's the smallest in its column
        for (uint8_t k = 0; k < rows; k++) {
          if (matrix[i][j] > matrix[k][j]) {
            is_saddle = false;
            break;
          }
        }
      }

      if (is_saddle) {
        points[total_saddle_points].row = i + 1;
        points[total_saddle_points].column = j + 1;
        total_saddle_points++;
      }
    }
  }

  if (total_saddle_points > 0) {
    result->points = (saddle_point_t *)malloc(total_saddle_points * sizeof(saddle_point_t));
    if (!result->points) {
        free(points);
        free(result);
        return NULL;
    }
    memcpy(result->points, points, total_saddle_points * sizeof(saddle_point_t));
  }

  free(points);
  result->count = total_saddle_points;
  return result;
}

void free_saddle_points(saddle_points_t *result) {
  if (result) {
    free(result->points);
    free(result);
  }
}