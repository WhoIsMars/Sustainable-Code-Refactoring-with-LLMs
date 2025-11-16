#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<uint32_t>> spiral_matrix(uint32_t size) {
    if (size == 0) return {};

    std::vector<std::vector<uint32_t>> out(size, std::vector<uint32_t>(size));
    uint32_t k = 1, top = 0, bottom = size - 1, left = 0, right = size - 1;

    while (top <= bottom && left <= right) {
        for (uint32_t col = left; col <= right; ++col) out[top][col] = k++;
        ++top;

        for (uint32_t row = top; row <= bottom; ++row) out[row][right] = k++;
        if (right-- < left) break;

        for (uint32_t col = right + 1; col-- > left;) out[bottom][col] = k++;
        if (bottom-- < top) break;

        for (uint32_t row = bottom + 1; row-- > top;) out[row][left] = k++;
        ++left;
    }

    return out;
}

}  // namespace spiral_matrix