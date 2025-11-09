#include "robot_simulator.h"

namespace robot_simulator {
    Robot::Robot() : Robot({0, 0}, Bearing::NORTH) {}

    Robot::Robot(std::pair<int, int> position, Bearing bearing)
        : _position_x(position.first), _position_y(position.second), _facing_direction(bearing) {}

    std::pair<int, int> Robot::get_position() const {
        return {_position_x, _position_y};
    }

    Bearing Robot::get_bearing() const {
        return _facing_direction;
    }

    void Robot::turn_right() {
        _facing_direction = static_cast<Bearing>((_facing_direction + 1) & 3);
    }

    void Robot::turn_left() {
        _facing_direction = static_cast<Bearing>((_facing_direction + 3) & 3);
    }

    void Robot::advance() {
        static const int dx[] = {0, 1, 0, -1};
        static const int dy[] = {1, 0, -1, 0};
        _position_x += dx[_facing_direction];
        _position_y += dy[_facing_direction];
    }

    void Robot::execute_sequence(const std::string& sequence) {
        for (char command : sequence) {
            if (command == 'R') {
                turn_right();
            } else if (command == 'L') {
                turn_left();
            } else if (command == 'A') {
                advance();
            }
        }
    }
}  // namespace robot_simulator