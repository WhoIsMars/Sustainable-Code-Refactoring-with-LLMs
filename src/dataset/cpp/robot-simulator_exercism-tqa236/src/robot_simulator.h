#pragma once
#include <string>

namespace robot_simulator {
using std::string;
using Coordination = std::pair<int, int>;

enum Bearing { NORTH, EAST, SOUTH, WEST };
class Robot {
 private:
  Coordination robot_position{0, 0};
  Bearing robot_bearing{NORTH};

 public:
  Robot();
  Robot(Coordination robot_position, Bearing robot_bearing);
  Coordination get_position() const { return robot_position; }
  Bearing get_bearing() const { return robot_bearing; }
  void turn_right();
  void turn_left();
  void advance();
  void execute_sequence(const string&);
};

}  // namespace robot_simulator
