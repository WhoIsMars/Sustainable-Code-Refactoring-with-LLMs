#include "robot_name.h"

#include <random>
#include <unordered_set>
#include <string>

namespace robot_name {
    std::unordered_set<std::string> robot::_existing_names = {};
    std::mt19937 robot::_rng{std::random_device{}()};
    std::uniform_int_distribution<int> robot::_char_dist('A', 'Z');
    std::uniform_int_distribution<int> robot::_digit_dist('0', '9');

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
        std::string name(5, '\0');

        do {
            name[0] = _generate_rand_char();
            name[1] = _generate_rand_char();
            name[2] = _generate_rand_digit();
            name[3] = _generate_rand_digit();
            name[4] = _generate_rand_digit();
        } while (!robot::_existing_names.insert(name).second);

        return name;
    }

    char robot::_generate_rand_char() {
        return static_cast<char>(_char_dist(_rng));
    }

    char robot::_generate_rand_digit() {
        return static_cast<char>(_digit_dist(_rng));
    }
}  // namespace robot_name