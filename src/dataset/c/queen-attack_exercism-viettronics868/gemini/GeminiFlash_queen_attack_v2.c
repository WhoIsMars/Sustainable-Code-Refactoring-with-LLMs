#include "queen_attack.h"
#include <stdlib.h>
#include <stdint.h>

attack_status_t can_attack(position_t queen_1, position_t queen_2){
    // Verify input positions are within the valid range (0-7)
    if (queen_1.row > 7 || queen_1.column > 7 || queen_2.row > 7 || queen_2.column > 7) {
        return INVALID_POSITION;
    }
    if (queen_1.row < 0 || queen_1.column < 0 || queen_2.row < 0 || queen_2.column < 0) {
        return INVALID_POSITION;
    }

    // If queens are in the same position, it's an invalid scenario
    if (queen_1.row == queen_2.row && queen_1.column == queen_2.column) {
        return INVALID_POSITION;
    }

    // Calculate the row and column differences using absolute values
    uint8_t row_diff = (queen_1.row > queen_2.row) ? (queen_1.row - queen_2.row) : (queen_2.row - queen_1.row);
    uint8_t col_diff = (queen_1.column > queen_2.column) ? (queen_1.column - queen_2.column) : (queen_2.column - queen_1.column);

    // Check if the queens are in the same row, column, or diagonal
    if (row_diff == col_diff || row_diff == 0 || col_diff == 0) {
        return CAN_ATTACK;
    } else {
        return CAN_NOT_ATTACK;
    }
}