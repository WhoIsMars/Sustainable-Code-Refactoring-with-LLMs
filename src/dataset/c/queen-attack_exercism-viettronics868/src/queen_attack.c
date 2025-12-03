#include "queen_attack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

attack_status_t can_attack(position_t queen_1, position_t queen_2){
   
    if ( //verify input 
       (queen_1.row > 7) || (queen_1.row < 0) ||
       (queen_1.column > 7) || (queen_1.column < 0) ||
       (queen_2.row > 7) || (queen_2.row < 0) ||
       (queen_2.column > 7) || (queen_2.column < 0)
        ) return INVALID_POSITION;
    
    uint8_t row_12 = abs((queen_1.row) - (queen_2.row));
    uint8_t col_12 = abs((queen_1.column) - (queen_2.column));
    
    if ((row_12 == 0) && (col_12 == 0)) // queen over queen
        return INVALID_POSITION;
    

    if ((row_12 == col_12) || (row_12 == 0) || (col_12 == 0)){
        return CAN_ATTACK;
    } else {
        return CAN_NOT_ATTACK;
    }
    
    
}
