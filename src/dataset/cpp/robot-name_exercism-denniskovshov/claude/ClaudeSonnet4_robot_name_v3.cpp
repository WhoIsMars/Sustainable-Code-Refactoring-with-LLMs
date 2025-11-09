#include "robot_name.h"

#include <random>
#include <algorithm>

namespace robot_name {
    std::unordered_set<std::string> robot::_existing_names = {};
    thread_local std::mt19937 generator{std::random_device{}()};
    thread_local std::uniform_int_distribution<int> char_dist(0, 25);
    thread_local std::uniform_int_distribution<int> digit_dist(0, 9);

    robot::robot() {
        _name = _generate_name();
    }

    std::string robot::name() const {
        return _name;
    }

    void robot::reset() {
        _name = _generate_name();
    }

    std::string robot::_generate_name() {
        std::string name;
        name.reserve(5);

        do {
            name.clear();
            name.push_back('A' + char_dist(generator));
            name.push_back('A' + char_dist(generator));
            name.push_back('0' + digit_dist(generator));
            name.push_back('0' + digit_dist(generator));
            name.push_back('0' + digit_dist(generator));
        } while (!robot::_existing_names.emplace(name).second);

        return name;
    }

    char robot::_generate_rand_char() {
        return 'A' + char_dist(generator);
    }

    char robot::_generate_rand_digit() {
        return '0' + digit_dist(generator);
    }
}  // namespace robot_name