#include "robot_name.h"

#include <string>
#include <random>
#include <algorithm>

namespace robot_name {

std::mt19937 robot::rng(std::random_device{}());
std::unordered_set<std::string> robot::_names_list;

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
        std::uniform_int_distribution<int> letter_dist(0, 25);
        new_name += static_cast<char>('A' + letter_dist(rng));
        new_name += static_cast<char>('A' + letter_dist(rng));

        std::uniform_int_distribution<int> digit_dist(0, 9);
        for (int i = 0; i < 3; ++i) {
            new_name += std::to_string(digit_dist(rng));
        }
    } while (_names_list.find(new_name) != _names_list.end());

    _name = new_name;
    _names_list.insert(_name);
}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name