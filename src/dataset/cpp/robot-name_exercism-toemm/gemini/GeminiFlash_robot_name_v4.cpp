#include "robot_name.h"

#include <string>
#include <random>

namespace robot_name {

std::unordered_set<std::string> robot::_names_list;
std::mt19937 robot::_rng(std::random_device{}());
std::uniform_int_distribution<> robot::_letter_dist(0, 25);
std::uniform_int_distribution<> robot::_number_dist(0, 9);

robot::robot() {
    generate_name();
}

const std::string robot::name() const {
    return _name;
}

void robot::generate_name() {
    std::string new_name;
    do {
        new_name.clear();
        new_name += static_cast<char>('A' + _letter_dist(_rng));
        new_name += static_cast<char>('A' + _letter_dist(_rng));
        new_name += std::to_string(_number_dist(_rng));
        new_name += std::to_string(_number_dist(_rng));
        new_name += std::to_string(_number_dist(_rng));
    } while (_names_list.find(new_name) != _names_list.end());

    _name = new_name;
    _names_list.insert(_name);
}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name