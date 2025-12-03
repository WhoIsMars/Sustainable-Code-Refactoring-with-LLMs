#include "robot_name.h"

#include <random>
#include <algorithm>

namespace robot_name {
    std::unordered_set<std::string> robot::_existing_names = {};
    std::mt19937 robot::_rng{std::random_device{}()};
    std::uniform_int_distribution<> robot::_char_dist{'A', 'Z'};
    std::uniform_int_distribution<> robot::_digit_dist{'0', '9'};

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
                _existing_names.insert(name);
                break;
            }
        }

        return name;
    }

    char robot::_generate_rand_char() {
        return _char_dist(_rng);
    }

    char robot::_generate_rand_digit() {
        return _digit_dist(_rng);
    }
}  // namespace robot_name