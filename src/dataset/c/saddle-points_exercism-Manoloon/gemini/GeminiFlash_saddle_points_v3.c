#include "saddle_points.h"
#include <limits.h>

saddle_points_t* saddle_points(int rows, int cols, unsigned char grid[rows][cols]) {
    saddle_points_t* result = malloc(sizeof(saddle_points_t));
    if (result == NULL) return NULL;

    result->points = malloc(rows * cols * sizeof(saddle_point_t));
    if (result->points == NULL) {
        free(result);
        return NULL;
    }

    result->count = 0;
    int count = 0;

    for (int r = 0; r < rows; r++) {
        unsigned char max_in_row = grid[r][0];
        int col_index_max = 0;

        for (int c = 1; c < cols; c++) {
            if (grid[r][c] > max_in_row) {
                max_in_row = grid[r][c];
                col_index_max = c;
            }
        }

        int is_saddle = 1;
        for (int m = 0; m < rows; m++) {
            if (grid[m][col_index_max] < max_in_row) {
                is_saddle = 0;
                break;
            }
        }

        if (is_saddle) {
            result->points[count].row = r + 1;
            result->points[count].column = col_index_max + 1;
            count++;
        }
    }

    result->count = count;
    return result;
}

void free_saddle_points(saddle_points_t *points) {
    if (points == NULL) return;
    free(points->points);
    free(points);
}