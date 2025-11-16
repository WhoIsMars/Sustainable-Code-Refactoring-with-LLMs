#include "pascals_triangle.h"

namespace pascals_triangle {

std::vector<std::vector<int>> generate_rows(int i) {
    std::vector<std::vector<int>> outer;
    if (i <= 0) return outer;

    outer.reserve(i); // Reserve memory upfront to avoid reallocations
    outer.push_back({1});

    for (int j = 1; j < i; ++j) {
        const std::vector<int>& last_row = outer.back();
        std::vector<int> row(j + 1, 1); // Initialize row with 1s

        for (std::size_t k = 1; k < j; ++k) {
            row[k] = last_row[k - 1] + last_row[k];
        }

        outer.push_back(std::move(row)); // Use move semantics to avoid copying
    }

    return outer;
}

}  // namespace pascals_triangle