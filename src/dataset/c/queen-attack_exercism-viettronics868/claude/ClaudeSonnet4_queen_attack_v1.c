#include "queen_attack.h"
#include <stdint.h>

attack_status_t can_attack(position_t queen_1, position_t queen_2){
    // Use unsigned comparison to check bounds in single operation
    if ((uint8_t)queen_1.row > 7 || (uint8_t)queen_1.column > 7 ||
        (uint8_t)queen_2.row > 7 || (uint8_t)queen_2.column > 7)
        return INVALID_POSITION;
    
    // Check if queens are on same position first (most likely invalid case)
    if (queen_1.row == queen_2.row && queen_1.column == queen_2.column)
        return INVALID_POSITION;
    
    // Calculate differences without abs() function call
    int8_t row_diff = queen_1.row - queen_2.row;
    int8_t col_diff = queen_1.column - queen_2.column;
    
    // Use bit manipulation to get absolute values
    uint8_t row_abs = (row_diff < 0) ? -row_diff : row_diff;
    uint8_t col_abs = (col_diff < 0) ? -col_diff : col_diff;
    
    // Queens can attack if on same row, column, or diagonal
    return (row_abs == col_abs || row_abs == 0 || col_abs == 0) ? 
           CAN_ATTACK : CAN_NOT_ATTACK;
}