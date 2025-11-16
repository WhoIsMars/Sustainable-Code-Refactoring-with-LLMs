#include "robot_name.h"

#include <string>
#include <random>
#include <thread>

namespace robot_name {

thread_local std::mt19937 generator(std::hash<std::thread::id>{}(std::this_thread::get_id()));
thread_local std::uniform_int_distribution<int> letter_dist(0, 25);
thread_local std::uniform_int_distribution<int> digit_dist(0, 9);

robot::robot() {
    generate_name();
}

const std::string& robot::name() const {
    return _name;
}

void robot::generate_name() {
    constexpr size_t name_length = 5;
    _name.clear();
    _name.reserve(name_length);
    
    do {
        _name.clear();
        _name += static_cast<char>('A' + letter_dist(generator));
        _name += static_cast<char>('A' + letter_dist(generator));
        _name += static_cast<char>('0' + digit_dist(generator));
        _name += static_cast<char>('0' + digit_dist(generator));
        _name += static_cast<char>('0' + digit_dist(generator));
    } while (!_names_list.insert(_name).second);
}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name