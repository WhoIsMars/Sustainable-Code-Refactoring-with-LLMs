#include "queen_attack.h"

static inline bool is_valid_position(position_t position) 
{
    return position.row < 8 && position.column < 8;
}

attack_status_t can_attack(position_t queen_1, position_t queen_2) 
{
    if (!is_valid_position(queen_1) || !is_valid_position(queen_2) || 
        (queen_1.row == queen_2.row && queen_1.column == queen_2.column)) 
        return INVALID_POSITION;

    int row_diff = queen_1.row - queen_2.row;
    int col_diff = queen_1.column - queen_2.column;

    return (row_diff == 0 || col_diff == 0 || abs(row_diff) == abs(col_diff)) 
           ? CAN_ATTACK 
           : CAN_NOT_ATTACK;
}