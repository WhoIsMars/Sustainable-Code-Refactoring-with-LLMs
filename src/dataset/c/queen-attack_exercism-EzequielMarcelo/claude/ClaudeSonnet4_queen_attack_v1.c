#include "queen_attack.h"

attack_status_t can_attack(position_t queen_1, position_t queen_2) 
{    
    // Check validity and same position in one pass
    if (queen_1.row >= 8 || queen_1.column >= 8 || 
        queen_2.row >= 8 || queen_2.column >= 8)
        return INVALID_POSITION;
    
    if (queen_1.row == queen_2.row && queen_1.column == queen_2.column) 
        return INVALID_POSITION;
    
    // Calculate differences once
    int row_diff = queen_1.row - queen_2.row;
    int col_diff = queen_1.column - queen_2.column;
    
    // Check all attack conditions efficiently
    if (row_diff == 0 || col_diff == 0 || 
        (row_diff < 0 ? -row_diff : row_diff) == (col_diff < 0 ? -col_diff : col_diff))
        return CAN_ATTACK;
    
    return CAN_NOT_ATTACK;
}