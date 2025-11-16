#include "pascals_triangle.h"

namespace pascals_triangle {

[[nodiscard]]
ptriangle_t generate_rows(const int &n) noexcept {
    if (n <= 0) return {};
    
    ptriangle_t ptriangle;
    ptriangle.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        std::vector<int> row;
        row.reserve(i + 1);
        
        row.push_back(1);
        for (int j = 1; j < i; ++j) {
            row.push_back(ptriangle[i-1][j-1] + ptriangle[i-1][j]);
        }
        if (i > 0) {
            row.push_back(1);
        }
        
        ptriangle.push_back(std::move(row));
    }
    return ptriangle;
}

}  // namespace pascals_triangle