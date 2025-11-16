#include "robot_name.h"

#include <string>
#include <random>

namespace robot_name {

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> letter_dist(0, 25);
std::uniform_int_distribution<> digit_dist(0, 9);

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
        new_name += static_cast<char>('A' + letter_dist(gen));
        new_name += static_cast<char>('A' + letter_dist(gen));
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
    } while (_names_list.count(new_name) > 0);

    _name = new_name;
    _names_list.insert(_name);
}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name