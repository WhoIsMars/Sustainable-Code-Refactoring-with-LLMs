#include "queen_attack.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

attack_status_t can_attack(position_t queen_1, position_t queen_2){
   
    if (queen_1.row > 7 || queen_1.row < 0 ||
        queen_1.column > 7 || queen_1.column < 0 ||
        queen_2.row > 7 || queen_2.row < 0 ||
        queen_2.column > 7 || queen_2.column < 0) {
        return INVALID_POSITION;
    }

    if (queen_1.row == queen_2.row && queen_1.column == queen_2.column) {
        return INVALID_POSITION;
    }

    uint8_t row_diff = (queen_1.row > queen_2.row) ? (queen_1.row - queen_2.row) : (queen_2.row - queen_1.row);
    uint8_t col_diff = (queen_1.column > queen_2.column) ? (queen_1.column - queen_2.column) : (queen_2.column - queen_1.column);

    if (row_diff == col_diff || queen_1.row == queen_2.row || queen_1.column == queen_2.column) {
        return CAN_ATTACK;
    } else {
        return CAN_NOT_ATTACK;
    }
}