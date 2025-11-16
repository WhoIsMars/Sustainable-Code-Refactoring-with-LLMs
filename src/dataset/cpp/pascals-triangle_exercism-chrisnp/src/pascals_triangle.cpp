#include "pascals_triangle.h"

namespace pascals_triangle {

[[nodiscard]]
ptriangle_t generate_rows(const int &n) noexcept {
    ptriangle_t ptriangle {};
    for (int i = 0; i < n; i++) {
        std::vector<int> row {};
        for (int j = 0; j <= i; j++) {
            row.push_back(binomial(i, j));
        }
        ptriangle.push_back(row);
    }
    return ptriangle;
}

}  // namespace pascals_triangle 



