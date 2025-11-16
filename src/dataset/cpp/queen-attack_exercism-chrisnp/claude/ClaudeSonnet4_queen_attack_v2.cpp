#include "queen_attack.h"
#include <sstream>

queen_attack::chess_board::chess_board(const square &white, const square &black) 
                           : white_queen { white }, black_queen { black } 
{
    if (black_queen == white_queen) {
        throw std::domain_error("Daahling, this is MY square");
    }
    if (!legal_position(black_queen)) {
        throw std::domain_error("Black queen not on board");
    } 
    if (!legal_position(white_queen)) {
        throw std::domain_error("White queen not on board");
    }
}

const square &queen_attack::chess_board::black() const noexcept
    { return black_queen; }

const square &queen_attack::chess_board::white() const noexcept
    { return white_queen; }

queen_attack::chess_board::operator std::string() const {
    std::string board;
    board.reserve(71); // 8*8 squares + 7 spaces per row + 8 newlines
    
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            if (file > 0) board += ' ';
            if (rank == black_queen.first && file == black_queen.second) {
                board += 'B';
            } else if (rank == white_queen.first && file == white_queen.second) {
                board += 'W';
            } else {
                board += '_';
            }
        }
        board += '\n';
    }
    return board;
}

bool queen_attack::chess_board::can_attack() const noexcept {
    int drank = abs(black_queen.first - white_queen.first);
    int dfile = abs(black_queen.second - white_queen.second); 
    
    return drank == 0 || dfile == 0 || drank == dfile;
}