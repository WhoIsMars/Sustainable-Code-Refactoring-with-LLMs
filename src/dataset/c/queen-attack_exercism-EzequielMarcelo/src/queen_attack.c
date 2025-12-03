#include "queen_attack.h"

static bool is_valid_position(position_t position) 
{
    return position.row < 8 && position.column < 8;
}

attack_status_t can_attack(position_t queen_1, position_t queen_2) 
{    
    if (!is_valid_position(queen_1) || !is_valid_position(queen_2)) 
        return INVALID_POSITION;    
    
    if (queen_1.row == queen_2.row && queen_1.column == queen_2.column) 
        return INVALID_POSITION;  
    
    if (queen_1.row == queen_2.row) 
        return CAN_ATTACK;
   
    if (queen_1.column == queen_2.column) 
        return CAN_ATTACK;    
    
    if (abs(queen_1.row - queen_2.row) == abs(queen_1.column - queen_2.column))
        return CAN_ATTACK;
    
    return CAN_NOT_ATTACK;
}