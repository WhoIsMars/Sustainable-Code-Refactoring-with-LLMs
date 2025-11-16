#pragma once
#include <stdlib.h>

#include <stdexcept>
#include <string>
#include <utility>

namespace queen_attack {
using std::domain_error;
using std::make_pair;
using std::string;
using Position = std::pair<int, int>;

class chess_board {
 private:
  Position white_position{0, 3};
  Position black_position{7, 3};
  unsigned get_queen_position_in_string(Position coordinates) const;

 public:
  chess_board();
  chess_board(Position white, Position black);
  Position white() const;
  Position black() const;
  bool can_attack() const;
  explicit operator string() const;
};

}  // namespace queen_attack
