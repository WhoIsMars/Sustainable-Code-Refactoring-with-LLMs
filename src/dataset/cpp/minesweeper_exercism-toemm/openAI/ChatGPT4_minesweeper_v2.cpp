#include "minesweeper.h"

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {
    if (input.empty()) return input;

    const std::size_t rows = input.size();
    const std::size_t cols = input[0].size();

    // Directions for adjacent cells
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            if (input[i][j] == '*') continue;

            int ctr = 0;
            for (int d = 0; d < 8; ++d) {
                std::size_t ni = i + dx[d];
                std::size_t nj = j + dy[d];

                if (ni < rows && nj < cols && input[ni][nj] == '*') {
                    ++ctr;
                }
            }

            if (ctr > 0) {
                input[i][j] = '0' + ctr;
            }
        }
    }

    return input;
}

}  // namespace minesweeper