#include "queen_attack.h"
#include <array>

queen_attack::chess_board::chess_board(const square &white, const square &black) 
    : white_queen{white}, black_queen{black} 
{
    if (black_queen == white_queen) {
        throw std::domain_error("Daahling, this is MY square");
    }
    if (!legal_position(black_queen) || !legal_position(white_queen)) {
        throw std::domain_error("Queen not on board");
    }
}

const square &queen_attack::chess_board::black() const noexcept {
    return black_queen;
}

const square &queen_attack::chess_board::white() const noexcept {
    return white_queen;
}

queen_attack::chess_board::operator std::string() const {
    std::array<std::array<char, 8>, 8> board{};
    for (auto &row : board) row.fill('_');
    board[white_queen.first][white_queen.second] = 'W';
    board[black_queen.first][black_queen.second] = 'B';

    std::string result;
    result.reserve(64 + 16); // 64 squares + 7 newlines + null terminator
    for (const auto &row : board) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (i > 0) result += ' ';
            result += row[i];
        }
        result += '\n';
    }
    return result;
}

bool queen_attack::chess_board::can_attack() const noexcept {
    int drank = black_queen.first - white_queen.first;
    int dfile = black_queen.second - white_queen.second;
    return drank == 0 || dfile == 0 || abs(drank) == abs(dfile);
}