#include "flower_field.h"

namespace flower_field {

std::vector<std::string> annotate(std::vector<std::string> board) {
    if (board.empty()) return board;

    const int rows = board.size();
    const int cols = board[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == '*') continue;

            int ctr = 0;
            
            // Check all 8 adjacent cells directly
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue; // Skip current cell
                    
                    int ni = i + dx;
                    int nj = j + dy;
                    
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == '*') {
                        ++ctr;
                    }
                }
            }

            if (ctr > 0) {
                board[i][j] = '0' + ctr;
            }
        }
    }

    return board;
}

}  // namespace flower_field