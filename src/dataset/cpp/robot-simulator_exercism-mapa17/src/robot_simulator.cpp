#include "robot_simulator.h"

#include <stdexcept>

namespace robot_simulator {
    using namespace std;

    const pair<int, int> Robot::get_position() const {
        return pair<int, int>(x, y);
    }

    Bearing Robot::get_bearing() const {
        return b;
    }

    void Robot::turn_right(){
        b = Bearing((4 + (b + 1))%4);
    }

    void Robot::turn_left(){
        b = Bearing((4 + (b - 1))%4);
    }

    void Robot::advance(){
        switch(b){
            case NORTH: y += 1; break;
            case EAST:  x += 1; break;
            case SOUTH: y -= 1; break;
            case WEST:  x -= 1; break;
        }
    }

    void Robot::execute_sequence(std::string op_sequence){
        for(const char& op : op_sequence){
            switch(op){
                case 'A': advance(); break;
                case 'L': turn_left(); break;
                case 'R': turn_right(); break;
                default: throw domain_error("Invalid operation!");
            }
        }
    }

}  // namespace robot_simulator
