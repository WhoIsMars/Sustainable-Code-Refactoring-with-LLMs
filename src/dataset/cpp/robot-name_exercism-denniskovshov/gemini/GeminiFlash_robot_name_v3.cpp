#include "robot_name.h"

#include <random>
#include <algorithm>

namespace robot_name {
    std::unordered_set<std::string> robot::_existing_names = {};
    std::mt19937 robot::_rng{std::random_device{}()};

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
        std::uniform_int_distribution<> dist(0, 25);
        return (char)('A' + dist(_rng));
    }

    char robot::_generate_rand_digit() {
        std::uniform_int_distribution<> dist(0, 9);
        return (char)('0' + dist(_rng));
    }
}  // namespace robot_name