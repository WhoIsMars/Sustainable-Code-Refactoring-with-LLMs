#include "pascals_triangle.h"

namespace pascals_triangle {

std::vector<std::vector<int>> generate_rows(int i) {


    std::vector<std::vector<int>> outer;

    if (i > 0) {

        outer.push_back({1});

        // i >= 1
        for (int j{1}; j < i; j++) {

            std::vector<int> row{1};

            std::vector<int> last_row = outer[j-1];

            for (std::size_t k{}; k < last_row.size()-1; k++) {

                row.push_back(last_row[k] + last_row[k+1]);

            }

            // add ending 1
            row.push_back(1);

            outer.push_back(row);

        }
    }

    return outer;


}

}  // namespace pascals_triangle
