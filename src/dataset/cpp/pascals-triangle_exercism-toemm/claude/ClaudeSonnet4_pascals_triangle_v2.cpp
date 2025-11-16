#include "pascals_triangle.h"

namespace pascals_triangle {

std::vector<std::vector<int>> generate_rows(int i) {
    if (i <= 0) {
        return {};
    }

    std::vector<std::vector<int>> outer;
    outer.reserve(i);
    
    outer.push_back({1});
    
    for (int j = 1; j < i; j++) {
        std::vector<int> row;
        row.reserve(j + 1);
        row.push_back(1);
        
        const std::vector<int>& last_row = outer[j-1];
        
        for (int k = 0; k < j - 1; k++) {
            row.push_back(last_row[k] + last_row[k+1]);
        }
        
        row.push_back(1);
        outer.push_back(std::move(row));
    }

    return outer;
}

}  // namespace pascals_triangle