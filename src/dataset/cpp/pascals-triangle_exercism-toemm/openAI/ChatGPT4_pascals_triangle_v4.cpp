#include "pascals_triangle.h"

namespace pascals_triangle {

std::vector<std::vector<int>> generate_rows(int i) {
    if (i <= 0) return {};

    std::vector<std::vector<int>> outer(i);
    outer[0] = {1};

    for (int j = 1; j < i; ++j) {
        outer[j].resize(j + 1);
        outer[j][0] = outer[j][j] = 1;

        for (int k = 1; k < j; ++k) {
            outer[j][k] = outer[j - 1][k - 1] + outer[j - 1][k];
        }
    }

    return outer;
}

}  // namespace pascals_triangle