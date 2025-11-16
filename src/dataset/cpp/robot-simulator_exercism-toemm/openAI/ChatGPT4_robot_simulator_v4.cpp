#include "robot_simulator.h"

namespace robot_simulator {

Robot::Robot(std::pair<int, int> position, Bearing bearing) : _pos(std::move(position)), _bearing(bearing) {}

Coordinates Robot::get_position() const {
    return _pos;
}

Bearing Robot::get_bearing() const {
    return _bearing;
}

void Robot::turn_right() {
    _bearing = static_cast<Bearing>((static_cast<int>(_bearing) + 1) % 4);
}

void Robot::turn_left() {
    _bearing = static_cast<Bearing>((static_cast<int>(_bearing) + 3) % 4);
}

void Robot::advance() {
    switch (_bearing) {
        case Bearing::NORTH: ++_pos.second; break;
        case Bearing::SOUTH: --_pos.second; break;
        case Bearing::EAST:  ++_pos.first;  break;
        case Bearing::WEST:  --_pos.first;  break;
    }
}

void Robot::execute_sequence(const std::string& seq) {
    for (char ch : seq) {
        switch (ch) {
            case 'R': turn_right(); break;
            case 'L': turn_left();  break;
            case 'A': advance();    break;
        }
    }
}

}  // namespace robot_simulator