#include "queen_attack.h"

#include <stdlib.h>

#define ROW_MAX (8)
#define COL_MAX (8)

attack_status_t can_attack(position_t queen_1, position_t queen_2)
{
    // Check bounds and same position in one condition
    if (queen_1.column >= COL_MAX 
        || queen_1.row >= ROW_MAX 
        || queen_2.column >= COL_MAX 
        || queen_2.row >= ROW_MAX
        || (queen_1.column == queen_2.column && queen_1.row == queen_2.row))
    {
        return INVALID_POSITION;
    }

    // Calculate differences once
    int col_diff = queen_1.column - queen_2.column;
    int row_diff = queen_1.row - queen_2.row;

    // Check attack conditions
    if (col_diff == 0 || row_diff == 0 || abs(col_diff) == abs(row_diff))
    {
        return CAN_ATTACK;
    }

    return CAN_NOT_ATTACK;
}