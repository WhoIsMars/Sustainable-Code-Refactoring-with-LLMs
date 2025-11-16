#include "minesweeper.h"

#include <algorithm>
#include <vector>

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {
    if (input.empty()) {
        return input;
    }

    const std::size_t num_rows = input.size();
    const std::size_t num_cols = input[0].size();

    std::vector<std::string> result = input;

    for (std::size_t i = 0; i < num_rows; ++i) {
        for (std::size_t j = 0; j < num_cols; ++j) {
            if (input[i][j] == '*') {
                continue;
            }

            int mine_count = 0;

            // Check neighbors
            for (int row_offset = -1; row_offset <= 1; ++row_offset) {
                for (int col_offset = -1; col_offset <= 1; ++col_offset) {
                    if (row_offset == 0 && col_offset == 0) {
                        continue;
                    }

                    int neighbor_row = static_cast<int>(i) + row_offset;
                    int neighbor_col = static_cast<int>(j) + col_offset;

                    if (neighbor_row >= 0 && neighbor_row < static_cast<int>(num_rows) &&
                        neighbor_col >= 0 && neighbor_col < static_cast<int>(num_cols)) {
                        if (input[neighbor_row][neighbor_col] == '*') {
                            mine_count++;
                        }
                    }
                }
            }

            if (mine_count > 0) {
                result[i][j] = '0' + mine_count;
            }
        }
    }

    return result;
}

}  // namespace minesweeper