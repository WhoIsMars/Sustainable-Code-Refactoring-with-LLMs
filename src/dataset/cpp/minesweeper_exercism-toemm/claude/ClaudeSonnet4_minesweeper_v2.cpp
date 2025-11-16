#include "minesweeper.h"

namespace minesweeper {

std::vector<std::string> annotate(std::vector<std::string> input) noexcept {

    if (input.empty()) return input;
    
    const std::size_t rows = input.size();
    const std::size_t cols = input[0].size();
    
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            
            if (input[i][j] == '*') continue;
            
            int ctr = 0;
            
            // Check all 8 adjacent cells
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;
                    
                    int ni = static_cast<int>(i) + di;
                    int nj = static_cast<int>(j) + dj;
                    
                    if (ni >= 0 && ni < static_cast<int>(rows) && 
                        nj >= 0 && nj < static_cast<int>(cols) && 
                        input[ni][nj] == '*') {
                        ctr++;
                    }
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