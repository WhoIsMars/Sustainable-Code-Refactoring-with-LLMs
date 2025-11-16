#include "flower_field.h"

namespace flower_field {


std::vector<std::string> annotate(std::vector<std::string> board) {

    if (board.size() == 0) return board;                    

    const int rows = board.size();
    const int cols = board[0].size();

    std::vector<int> delta{-1, 0, 1};

    for (int i{}; i < rows; ++i) {

        for (int j{}; j < cols; ++j) {

            int ctr{};

            if (board[i][j] == '*') continue;

            for (auto dx : delta) {

                for (auto dy : delta) {

                    int ni = i + dx;
                    int nj = j + dy;

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                        if (board[ni][nj] == '*') ctr++;
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
