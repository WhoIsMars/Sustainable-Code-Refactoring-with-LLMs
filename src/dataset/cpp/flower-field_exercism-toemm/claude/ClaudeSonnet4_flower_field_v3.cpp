#include "flower_field.h"

namespace flower_field {

std::vector<std::string> annotate(std::vector<std::string> board) {
    if (board.empty()) return board;

    const int rows = static_cast<int>(board.size());
    const int cols = static_cast<int>(board[0].size());
    
    constexpr int deltas[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == '*') continue;

            int count = 0;
            for (const auto& delta : deltas) {
                const int ni = i + delta[0];
                const int nj = j + delta[1];
                
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == '*') {
                    ++count;
                }
            }

            if (count > 0) {
                board[i][j] = static_cast<char>('0' + count);
            }
        }
    }

    return board;
}

}  // namespace flower_field