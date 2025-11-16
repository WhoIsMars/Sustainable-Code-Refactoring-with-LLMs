#include "minesweeper.h"
#include <algorithm>

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {
    if (input.empty()) return input;

    size_t num_rows = input.size();
    size_t num_cols = input[0].size();

    std::vector<std::string> result = input;

    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t j = 0; j < num_cols; ++j) {
            if (input[i][j] == '*') continue;

            int mine_count = 0;

            // Check neighbors
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (x == 0 && y == 0) continue; // Skip the current cell

                    int row = i + x;
                    int col = j + y;

                    if (row >= 0 && row < num_rows && col >= 0 && col < num_cols && input[row][col] == '*') {
                        mine_count++;
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