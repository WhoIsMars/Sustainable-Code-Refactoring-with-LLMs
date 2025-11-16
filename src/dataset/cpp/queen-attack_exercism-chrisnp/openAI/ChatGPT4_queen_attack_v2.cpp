#include "queen_attack.h"
#include <string>

queen_attack::chess_board::chess_board(const square &white, const square &black) 
    : white_queen{white}, black_queen{black} 
{
    if (black_queen == white_queen) {
        throw std::domain_error("Queens cannot occupy the same square");
    }
    if (!legal_position(black_queen) || !legal_position(white_queen)) {
        throw std::domain_error("Queen position out of bounds");
    }
}

const square &queen_attack::chess_board::black() const noexcept {
    return black_queen;
}

const square &queen_attack::chess_board::white() const noexcept {
    return white_queen;
}

queen_attack::chess_board::operator std::string() const {
    std::string board(64 * 2 - 1, '_');
    for (int i = 7; i > 0; --i) board.insert(i * 16 - 1, "\n");

    board[white_queen.first * 16 + white_queen.second * 2] = 'W';
    board[black_queen.first * 16 + black_queen.second * 2] = 'B';

    return board;
}

bool queen_attack::chess_board::can_attack() const noexcept {
    int drank = black_queen.first - white_queen.first;
    int dfile = black_queen.second - white_queen.second;

    return drank == 0 || dfile == 0 || abs(drank) == abs(dfile);
}