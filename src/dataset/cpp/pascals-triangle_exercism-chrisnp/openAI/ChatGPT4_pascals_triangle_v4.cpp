#include "pascals_triangle.h"

namespace pascals_triangle {

[[nodiscard]]
ptriangle_t generate_rows(const int &n) noexcept {
    ptriangle_t ptriangle;
    ptriangle.reserve(n);
    for (int i = 0; i < n; i++) {
        std::vector<int> row(i + 1, 1);
        for (int j = 1; j < i; j++) {
            row[j] = ptriangle[i - 1][j - 1] + ptriangle[i - 1][j];
        }
        ptriangle.push_back(std::move(row));
    }
    return ptriangle;
}

}  // namespace pascals_triangle