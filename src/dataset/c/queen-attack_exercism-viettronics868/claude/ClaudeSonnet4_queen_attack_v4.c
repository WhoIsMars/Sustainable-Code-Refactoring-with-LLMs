#include "queen_attack.h"
#include <stdint.h>

attack_status_t can_attack(position_t queen_1, position_t queen_2){
    
    if (((uint8_t)queen_1.row > 7) || ((uint8_t)queen_1.column > 7) ||
        ((uint8_t)queen_2.row > 7) || ((uint8_t)queen_2.column > 7))
        return INVALID_POSITION;
    
    int8_t row_diff = queen_1.row - queen_2.row;
    int8_t col_diff = queen_1.column - queen_2.column;
    
    if ((row_diff == 0) && (col_diff == 0))
        return INVALID_POSITION;
    
    if ((row_diff == 0) || (col_diff == 0) || 
        (row_diff == col_diff) || (row_diff == -col_diff))
        return CAN_ATTACK;
    
    return CAN_NOT_ATTACK;
}