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
    _bearing = static_cast<Bearing>((static_cast<int>(_bearing) + 1) & 3);
}

void Robot::turn_left() {
    _bearing = static_cast<Bearing>((static_cast<int>(_bearing) + 3) & 3);
}

void Robot::advance() {
    static constexpr int dx[] = {0, 1, 0, -1};
    static constexpr int dy[] = {1, 0, -1, 0};
    
    const int bearing_idx = static_cast<int>(_bearing);
    _pos.first += dx[bearing_idx];
    _pos.second += dy[bearing_idx];
}

void Robot::execute_sequence(const std::string& seq) {
    for (char ch : seq) {
        switch (ch) {
            case 'R': turn_right(); break;
            case 'L': turn_left(); break;
            case 'A': advance(); break;
        }
    }
}

}  // namespace robot_simulator