#include "robot_simulator.h"

namespace robot_simulator {
    Robot::Robot() : Robot(std::make_pair(0, 0), Bearing::NORTH) {
    }

    Robot::Robot(std::pair<int, int> position, Bearing bearing) : _position(position), _facing_direction(bearing) {
    }

    std::pair<int, int> Robot::get_position() const {
        return _position;
    }

    Bearing Robot::get_bearing() const {
        return _facing_direction;
    }

    void Robot::turn_right() {
        _facing_direction = static_cast<Bearing>((_facing_direction + 1) % 4);
    }

    void Robot::turn_left() {
        _facing_direction = static_cast<Bearing>((_facing_direction + 3) % 4);
    }

    void Robot::advance() {
        switch (_facing_direction)
        {
            case NORTH:
                _position.second++;
                break;

            case EAST:
                _position.first++;
                break;

            case SOUTH:
                _position.second--;
                break;

            case WEST:
                _position.first--;
                break;
        }
    }

    void Robot::execute_sequence(const std::string& sequence) {
        for (char command : sequence) {
            switch (command)
            {
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