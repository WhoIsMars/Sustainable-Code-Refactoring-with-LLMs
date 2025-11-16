#include "spiral_matrix.h"

namespace spiral_matrix {

std::vector<std::vector<uint32_t>> spiral_matrix(uint32_t size) {
    if (size == 0) {
        return {};
    }
    
    std::vector<std::vector<uint32_t>> out;
    out.reserve(size);
    for (uint32_t i = 0; i < size; ++i) {
        out.emplace_back(size);
    }

    uint32_t k = 1;
    uint32_t top = 0;
    uint32_t bottom = size - 1;
    uint32_t left = 0;
    uint32_t right = size - 1;

    while (top <= bottom && left <= right) {
        for (uint32_t col = left; col <= right; ++col) {
            out[top][col] = k++;
        }
        if (++top > bottom) break;

        for (uint32_t row = top; row <= bottom; ++row) {
            out[row][right] = k++;
        }
        if (right-- == 0 || right < left) break;

        for (uint32_t col = right + 1; col-- > left;) {
            out[bottom][col] = k++;
        }
        if (bottom-- == 0 || bottom < top) break;

        for (uint32_t row = bottom + 1; row-- > top;) {
            out[row][left] = k++;
        }
        ++left;
    }

    return out;
}

}  // namespace spiral_matrix