#include "queen_attack.h"
#include <stdint.h>

attack_status_t can_attack(position_t queen_1, position_t queen_2) {
    // Verify input
    if (queen_1.row > 7 || queen_1.row < 0 || queen_1.column > 7 || queen_1.column < 0 ||
        queen_2.row > 7 || queen_2.row < 0 || queen_2.column > 7 || queen_2.column < 0) {
        return INVALID_POSITION;
    }

    // Check if queens overlap
    if (queen_1.row == queen_2.row && queen_1.column == queen_2.column) {
        return INVALID_POSITION;
    }

    // Check attack conditions
    if (queen_1.row == queen_2.row || queen_1.column == queen_2.column ||
        abs(queen_1.row - queen_2.row) == abs(queen_1.column - queen_2.column)) {
        return CAN_ATTACK;
    }

    return CAN_NOT_ATTACK;
}