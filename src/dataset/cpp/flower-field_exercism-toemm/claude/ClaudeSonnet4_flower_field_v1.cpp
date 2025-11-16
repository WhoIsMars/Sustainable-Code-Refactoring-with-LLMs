#include "flower_field.h"

namespace flower_field {

std::vector<std::string> annotate(std::vector<std::string> board) {
    if (board.empty()) return board;

    const int rows = static_cast<int>(board.size());
    const int cols = static_cast<int>(board[0].size());

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == '*') continue;

            int ctr = 0;
            
            // Check all 8 neighbors directly without nested loops
            const int start_row = (i > 0) ? i - 1 : i;
            const int end_row = (i < rows - 1) ? i + 1 : i;
            const int start_col = (j > 0) ? j - 1 : j;
            const int end_col = (j < cols - 1) ? j + 1 : j;

            for (int ni = start_row; ni <= end_row; ++ni) {
                for (int nj = start_col; nj <= end_col; ++nj) {
                    if (ni != i || nj != j) {
                        if (board[ni][nj] == '*') ++ctr;
                    }
                }
            }

            if (ctr > 0) {
                board[i][j] = static_cast<char>('0' + ctr);
            }
        }
    }

    return board;
}

}  // namespace flower_field