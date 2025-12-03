#include "queen_attack.h"

static inline bool is_valid_position(const position_t position) 
{
    return position.row < 8 && position.column < 8;
}

attack_status_t can_attack(const position_t queen_1, const position_t queen_2) 
{    
    if (!is_valid_position(queen_1) || !is_valid_position(queen_2) || 
        (queen_1.row == queen_2.row && queen_1.column == queen_2.column)) 
        return INVALID_POSITION;    
    
    return (queen_1.row == queen_2.row || 
            queen_1.column == queen_2.column || 
            abs(queen_1.row - queen_2.row) == abs(queen_1.column - queen_2.column)) 
            ? CAN_ATTACK : CAN_NOT_ATTACK;
}