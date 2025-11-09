#include "robot_name.h"

#include <array>
#include <random>

namespace robot_name {
    std::unordered_set<std::string> robot::_existing_names = {};
    std::mt19937 robot::_generator(std::random_device{}());
    std::uniform_int_distribution<> robot::_char_distribution(0, 25);
    std::uniform_int_distribution<> robot::_digit_distribution(0, 9);

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

        while (true) {
            name.clear();
            name.push_back(_generate_rand_char());
            name.push_back(_generate_rand_char());
            name.push_back(_generate_rand_digit());
            name.push_back(_generate_rand_digit());
            name.push_back(_generate_rand_digit());

            if (_existing_names.find(name) == _existing_names.end()) {
                _existing_names.emplace(name);
                break;
            }
        }

        return name;
    }

    char robot::_generate_rand_char() {
        return (char)('A' + _char_distribution(_generator));
    }

    char robot::_generate_rand_digit() {
        return (char)('0' + _digit_distribution(_generator));
    }
}  // namespace robot_name