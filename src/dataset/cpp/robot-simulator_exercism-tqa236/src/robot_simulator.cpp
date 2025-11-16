#include "robot_simulator.h"

namespace robot_simulator {

Robot::Robot() = default;
Robot::Robot(Coordination robot_position, Bearing robot_bearing)
    : robot_position{robot_position}, robot_bearing{robot_bearing} {}

void Robot::turn_right() {
  robot_bearing =
      robot_bearing == WEST ? NORTH : static_cast<Bearing>(robot_bearing + 1);
}

void Robot::turn_left() {
  robot_bearing =
      robot_bearing == NORTH ? WEST : static_cast<Bearing>(robot_bearing - 1);
}

void Robot::advance() {
  switch (robot_bearing) {
    case NORTH:
      robot_position.second = robot_position.second + 1;
      break;
    case EAST:
      robot_position.first = robot_position.first + 1;
      break;
    case SOUTH:
      robot_position.second = robot_position.second - 1;
      break;
    case WEST:
      robot_position.first = robot_position.first - 1;
      break;
  }
}

void Robot::execute_sequence(const string& sequence) {
  for (const char& action : sequence) {
    switch (action) {
      case 'R':
        turn_right();
        break;
      case 'L':
        turn_left();
        break;
      case 'A':
        advance();
        break;
    }
  }
}
}  // namespace robot_simulator
