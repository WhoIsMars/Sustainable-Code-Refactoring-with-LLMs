#include "queen_attack.h"

attack_status_t can_attack(position_t queen_1, position_t queen_2)
{
    // Check for invalid positions first (most likely to fail fast)
    if (queen_1.column >= 8 || queen_1.row >= 8 || 
        queen_2.column >= 8 || queen_2.row >= 8)
    {
        return INVALID_POSITION;
    }
    
    // Check if queens are on same position
    if (queen_1.column == queen_2.column && queen_1.row == queen_2.row)
    {
        return INVALID_POSITION;
    }
    
    // Check if queens can attack each other
    if (queen_1.column == queen_2.column || 
        queen_1.row == queen_2.row)
    {
        return CAN_ATTACK;
    }
    
    // Check diagonal attack using bit operations for efficiency
    int col_diff = queen_1.column - queen_2.column;
    int row_diff = queen_1.row - queen_2.row;
    
    // Use bitwise operations to get absolute values and compare
    col_diff = (col_diff ^ (col_diff >> 31)) - (col_diff >> 31);
    row_diff = (row_diff ^ (row_diff >> 31)) - (row_diff >> 31);
    
    return (col_diff == row_diff) ? CAN_ATTACK : CAN_NOT_ATTACK;
}