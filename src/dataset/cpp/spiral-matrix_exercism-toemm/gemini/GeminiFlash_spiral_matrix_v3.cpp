#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<uint32_t>> spiral_matrix(uint32_t size) {
    std::vector<std::vector<uint32_t>> out(size, std::vector<uint32_t>(size));

    uint32_t k = 1;
    uint32_t top = 0;
    uint32_t bottom = size - 1;
    uint32_t left = 0;
    uint32_t right = size - 1;

    while (top <= bottom && left <= right) {
        // left to right
        for (uint32_t col = left; col <= right; ++col) {
            out[top][col] = k++;
        }
        ++top;

        // top to bottom
        for (uint32_t row = top; row <= bottom; ++row) {
            out[row][right] = k++;
        }
        --right;

        // right to left
        if (top <= bottom) {
            for (uint32_t col = right; col >= left; --col) {
                out[bottom][col] = k++;
            }
            --bottom;
        }

        // bottom to top
        if (left <= right) {
            for (uint32_t row = bottom; row >= top; --row) {
                out[row][left] = k++;
            }
            ++left;
        }
    }

    return out;
}

}  // namespace spiral_matrix