#include "pascals_triangle.h"

namespace pascals_triangle {

[[nodiscard]]
ptriangle_t generate_rows(const int &n) noexcept {
    ptriangle_t ptriangle(n);
    for (int i = 0; i < n; i++) {
        ptriangle[i].resize(i + 1);
        ptriangle[i][0] = ptriangle[i][i] = 1;
        for (int j = 1; j < i; j++) {
            ptriangle[i][j] = ptriangle[i - 1][j - 1] + ptriangle[i - 1][j];
        }
    }
    return ptriangle;
}

}  // namespace pascals_triangle