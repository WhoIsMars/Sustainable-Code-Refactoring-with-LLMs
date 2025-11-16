#include "robot_name.h"

#include <string>
#include <iostream>
#include <ctime>

namespace robot_name {


robot::robot() {
    generate_name();
}


const std::string robot::name() const {
    return _name;

}

void robot::generate_name() {
    _name = ""; // reset

    _name += static_cast<char>('A' + std::rand() % 26);
    _name += static_cast<char>('A' + std::rand() % 26);


    _name += std::to_string(std::rand() % 10);
    _name += std::to_string(std::rand() % 10);
    _name += std::to_string(std::rand() % 10);

    if (_names_list.find(_name) == _names_list.end())
        _names_list.insert(_name);
    else
        generate_name();

}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name
