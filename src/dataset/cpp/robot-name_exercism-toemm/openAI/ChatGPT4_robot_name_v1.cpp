#include "robot_name.h"

#include <string>
#include <unordered_set>
#include <random>

namespace robot_name {

namespace {
    std::unordered_set<std::string> _names_list;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string generate_random_name() {
        std::string name;
        name += static_cast<char>(letter_dist(rng));
        name += static_cast<char>(letter_dist(rng));
        name += std::to_string(digit_dist(rng));
        name += std::to_string(digit_dist(rng));
        name += std::to_string(digit_dist(rng));
        return name;
    }
}

robot::robot() {
    generate_name();
}

const std::string robot::name() const {
    return _name;
}

void robot::generate_name() {
    do {
        _name = generate_random_name();
    } while (!_names_list.insert(_name).second);
}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name