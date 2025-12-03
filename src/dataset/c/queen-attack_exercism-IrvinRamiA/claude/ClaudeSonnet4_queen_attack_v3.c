#include "queen_attack.h"

attack_status_t can_attack(position_t queen_1, position_t queen_2)
{
    if ((queen_1.column | queen_1.row | queen_2.column | queen_2.row) >= 8)
        return INVALID_POSITION;
    
    if ((queen_1.column ^ queen_2.column) == 0 && (queen_1.row ^ queen_2.row) == 0)
        return INVALID_POSITION;
    
    int col_diff = queen_1.column - queen_2.column;
    int row_diff = queen_1.row - queen_2.row;
    
    if (col_diff == 0 || row_diff == 0 || 
        ((col_diff ^ row_diff) == 0) || ((col_diff ^ -row_diff) == 0))
        return CAN_ATTACK;
    
    return CAN_NOT_ATTACK;
}