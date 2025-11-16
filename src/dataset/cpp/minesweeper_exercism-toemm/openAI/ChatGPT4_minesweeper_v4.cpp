#include "minesweeper.h"

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {
    if (input.empty()) return input;

    const std::size_t rows = input.size();
    const std::size_t cols = input[0].size();

    std::vector<std::vector<int>> mine_count(rows, std::vector<int>(cols, 0));

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            if (input[i][j] == '*') {
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        std::size_t ni = i + di, nj = j + dj;
                        if (di == 0 && dj == 0) continue;
                        if (ni < rows && nj < cols) {
                            ++mine_count[ni][nj];
                        }
                    }
                }
            }
        }
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            if (input[i][j] != '*' && mine_count[i][j] > 0) {
                input[i][j] = '0' + mine_count[i][j];
            }
        }
    }

    return input;
}

}  // namespace minesweeper