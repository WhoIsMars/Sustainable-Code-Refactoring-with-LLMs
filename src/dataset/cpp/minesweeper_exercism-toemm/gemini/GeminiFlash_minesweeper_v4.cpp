#include "minesweeper.h"

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {
    if (input.empty()) {
        return input;
    }

    int rows = input.size();
    int cols = input[0].size();

    std::vector<std::string> result = input;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (input[i][j] == '*') continue;

            int mine_count = 0;

            for (int x = std::max(0, i - 1); x <= std::min(rows - 1, i + 1); ++x) {
                for (int y = std::max(0, j - 1); y <= std::min(cols - 1, j + 1); ++y) {
                    if (x == i && y == j) continue;
                    if (input[x][y] == '*') {
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