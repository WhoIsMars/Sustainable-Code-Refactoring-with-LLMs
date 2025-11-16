#include "robot_simulator.h"

namespace robot_simulator {

Robot::Robot(std::pair<int, int> position, Bearing bearing) : _bearing(bearing), _pos(position) {}

Coordinates Robot::get_position() const {
    return _pos;
}

Bearing Robot::get_bearing() const {
    return _bearing;
}

void Robot::turn_right() {
    switch (_bearing) {
        case Bearing::NORTH: _bearing = Bearing::EAST; break;
        case Bearing::SOUTH: _bearing = Bearing::WEST; break;
        case Bearing::EAST: _bearing = Bearing::SOUTH; break;
        case Bearing::WEST: _bearing = Bearing::NORTH; break;
        default: break; // Add a default case for safety
    }
}

void Robot::turn_left() {
    switch (_bearing) {
        case Bearing::NORTH: _bearing = Bearing::WEST; break;
        case Bearing::SOUTH: _bearing = Bearing::EAST; break;
        case Bearing::EAST: _bearing = Bearing::NORTH; break;
        case Bearing::WEST: _bearing = Bearing::SOUTH; break;
        default: break; // Add a default case for safety
    }
}

void Robot::advance() {
    switch (_bearing) {
        case Bearing::NORTH: _pos.second++; break;
        case Bearing::SOUTH: _pos.second--; break;
        case Bearing::EAST: _pos.first++; break;
        case Bearing::WEST: _pos.first--; break;
        default: break; // Add a default case for safety
    }
}

void Robot::execute_sequence(const std::string& seq) {
    for (const char& ch : seq) {
        switch (ch) {
            case 'R': turn_right(); break;
            case 'L': turn_left(); break;
            case 'A': advance(); break;
            default: break; // Ignore invalid characters
        }
    }
}

}  // namespace robot_simulator