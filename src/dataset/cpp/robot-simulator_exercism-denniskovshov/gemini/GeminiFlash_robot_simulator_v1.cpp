#include "robot_simulator.h"

namespace robot_simulator {

Robot::Robot() : _position_x(0), _position_y(0), _facing_direction(Bearing::NORTH) {}

Robot::Robot(std::pair<int, int> position, Bearing bearing)
    : _position_x(position.first), _position_y(position.second), _facing_direction(bearing) {}

std::pair<int, int> Robot::get_position() const {
    return {_position_x, _position_y};
}

Bearing Robot::get_bearing() const {
    return _facing_direction;
}

void Robot::turn_right() {
    _facing_direction = static_cast<Bearing>((_facing_direction + 1) & 0x3);
}

void Robot::turn_left() {
    _facing_direction = static_cast<Bearing>((_facing_direction + 3) & 0x3);
}

void Robot::advance() {
    switch (_facing_direction) {
        case NORTH:
            ++_position_y;
            break;
        case EAST:
            ++_position_x;
            break;
        case SOUTH:
            --_position_y;
            break;
        case WEST:
            --_position_x;
            break;
        default:
            // Handle unexpected bearing (optional, but good practice)
            break;
    }
}

void Robot::execute_sequence(const std::string& sequence) {
    for (char command : sequence) {
        switch (command) {
            case 'R':
                turn_right();
                break;
            case 'L':
                turn_left();
                break;
            case 'A':
                advance();
                break;
            default:
                // Handle unexpected command (optional, but good practice)
                break;
        }
    }
}

}  // namespace robot_simulator