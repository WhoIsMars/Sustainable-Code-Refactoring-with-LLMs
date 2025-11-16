#include "flower_field.h"

namespace flower_field {

std::vector<std::string> annotate(std::vector<std::string> board) {
    if (board.empty()) {
        return board;
    }

    const int rows = board.size();
    const int cols = board[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == '*') {
                continue;
            }

            int mine_count = 0;

            // Iterate over the 8 neighbors
            for (int x = std::max(0, i - 1); x <= std::min(rows - 1, i + 1); ++x) {
                for (int y = std::max(0, j - 1); y <= std::min(cols - 1, j + 1); ++y) {
                    if (x == i && y == j) {
                        continue; // Skip the current cell
                    }
                    if (board[x][y] == '*') {
                        mine_count++;
                    }
                }
            }

            if (mine_count > 0) {
                board[i][j] = '0' + mine_count;
            }
        }
    }

    return board;
}

} // namespace flower_field