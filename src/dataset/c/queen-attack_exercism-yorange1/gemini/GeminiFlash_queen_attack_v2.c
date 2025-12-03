#include "queen_attack.h"

#include <stdlib.h>
#include <math.h>

#define ROW_MAX (8)
#define COL_MAX (8)

attack_status_t can_attack(position_t queen_1, position_t queen_2) {
    if (queen_1.column >= COL_MAX || queen_1.row >= ROW_MAX ||
        queen_2.column >= COL_MAX || queen_2.row >= ROW_MAX ||
        (queen_1.column == queen_2.column && queen_1.row == queen_2.row)) {
        return INVALID_POSITION;
    }

    if (queen_1.column == queen_2.column || queen_1.row == queen_2.row) {
        return CAN_ATTACK;
    }

    if (abs(queen_1.column - queen_2.column) == abs(queen_1.row - queen_2.row)) {
        return CAN_ATTACK;
    }

    return CAN_NOT_ATTACK;
}