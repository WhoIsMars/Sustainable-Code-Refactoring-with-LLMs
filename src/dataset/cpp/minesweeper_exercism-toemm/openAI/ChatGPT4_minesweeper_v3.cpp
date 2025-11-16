#include "minesweeper.h"

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {
    if (input.empty()) return input;

    const std::size_t rows = input.size();
    const std::size_t cols = input[0].size();

    auto is_mine = [&](std::size_t x, std::size_t y) -> bool {
        return x < rows && y < cols && input[x][y] == '*';
    };

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            if (input[i][j] == '*') continue;

            int ctr = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    if (is_mine(i + dx, j + dy)) ++ctr;
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