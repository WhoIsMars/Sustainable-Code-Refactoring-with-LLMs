#include "saddle_points.h"
#include <limits.h>

saddle_points_t* saddle_points(int rows, int cols, unsigned char grid[rows][cols]) {
    saddle_points_t* result = malloc(sizeof(saddle_points_t));
    if (result == NULL) return NULL;

    // Initial allocation, can be realloc'd later if needed.  A reasonable starting size.
    result->points = malloc(rows * cols * sizeof(saddle_point_t));
    if (result->points == NULL) {
        free(result);
        return NULL;
    }

    int count = 0;
    for (int r = 0; r < rows; r++) {
        unsigned char row_max = 0;
        int col_index_at_row_max = -1;

        // Find the maximum value in the current row and its column index.
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] >= row_max) { // Changed > to >= to handle duplicate max values, and pick the last one.
                row_max = grid[r][c];
                col_index_at_row_max = c;
            }
        }

        // Check if the maximum value in the row is also the minimum value in its column.
        if (col_index_at_row_max != -1) {
            int is_saddle = 1;
            for (int m = 0; m < rows; m++) {
                if (grid[m][col_index_at_row_max] < row_max) {
                    is_saddle = 0;
                    break;
                }
            }

            if (is_saddle) {
                result->points[count].row = r + 1;
                result->points[count].column = col_index_at_row_max + 1;
                count++;
            }
        }
    }

    result->count = count;

    // Reallocate memory to the exact size needed
    if (count > 0) {
        saddle_point_t* temp = realloc(result->points, count * sizeof(saddle_point_t));
        if (temp != NULL) {
            result->points = temp;
        } // else realloc failed, but we still have a valid result, just potentially with extra allocated memory
    } else {
        free(result->points);
        result->points = NULL;
    }

    return result;
}

void free_saddle_points(saddle_points_t *points) {
    if (points == NULL) return;
    free(points->points);
    free(points);
}