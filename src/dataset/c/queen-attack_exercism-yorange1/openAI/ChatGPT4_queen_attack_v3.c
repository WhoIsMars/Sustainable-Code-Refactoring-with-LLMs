#include "queen_attack.h"

#include <stdlib.h>

#define BOARD_SIZE (8)

attack_status_t can_attack(position_t queen_1, position_t queen_2)
{
    if (queen_1.column >= BOARD_SIZE || queen_1.row >= BOARD_SIZE ||
        queen_2.column >= BOARD_SIZE || queen_2.row >= BOARD_SIZE ||
        (queen_1.column == queen_2.column && queen_1.row == queen_2.row))
    {
        return INVALID_POSITION;
    }

    int col_diff = abs(queen_1.column - queen_2.column);
    int row_diff = abs(queen_1.row - queen_2.row);

    if (queen_1.column == queen_2.column || queen_1.row == queen_2.row || col_diff == row_diff)
    {
        return CAN_ATTACK;
    }

    return CAN_NOT_ATTACK;
}