#include "queen_attack.h"
#include <stdlib.h>

static bool is_valid_position(position_t position) {
  return position.row < 8 && position.column < 8;
}

attack_status_t can_attack(position_t queen_1, position_t queen_2) {
  if (!is_valid_position(queen_1) || !is_valid_position(queen_2)) {
    return INVALID_POSITION;
  }

  if (queen_1.row == queen_2.row && queen_1.column == queen_2.column) {
    return INVALID_POSITION;
  }

  if (queen_1.row == queen_2.row || queen_1.column == queen_2.column) {
    return CAN_ATTACK;
  }

  int row_diff = queen_1.row - queen_2.row;
  int col_diff = queen_1.column - queen_2.column;

  if (abs(row_diff) == abs(col_diff)) {
    return CAN_ATTACK;
  }

  return CAN_NOT_ATTACK;
}