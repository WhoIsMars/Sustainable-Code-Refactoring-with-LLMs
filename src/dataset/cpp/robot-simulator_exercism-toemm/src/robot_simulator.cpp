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

    switch (_bearing)
    {
    case Bearing::NORTH: _bearing = Bearing::EAST; break;
    case Bearing::SOUTH: _bearing = Bearing::WEST; break;
    case Bearing::EAST: _bearing = Bearing::SOUTH; break;
    case Bearing::WEST: _bearing = Bearing::NORTH; break;
    }



}
void Robot::turn_left() {

    switch (_bearing)
    {
    case Bearing::NORTH: _bearing = Bearing::WEST; break;
    case Bearing::SOUTH: _bearing = Bearing::EAST; break;
    case Bearing::EAST: _bearing = Bearing::NORTH; break;
    case Bearing::WEST: _bearing = Bearing::SOUTH; break;
    }

}

void Robot::advance() {

    auto& x = _pos.first;
    auto& y = _pos.second;

    switch (_bearing)
    {
    case Bearing::NORTH: y++; break;
    case Bearing::SOUTH: y--; break;
    case Bearing::EAST: x++; break;
    case Bearing::WEST: x--; break;
    }





}

void Robot::execute_sequence(const std::string& seq) { 
    
    
    for (const auto& ch : seq) {
        if (ch == 'R') turn_right();
        if (ch == 'L') turn_left();
        if (ch == 'A') advance();
    }
    



}
}  // namespace robot_simulator
