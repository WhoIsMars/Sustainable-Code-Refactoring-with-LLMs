#include "robot_name.h"

#include <string>
#include <random>
#include <unordered_set>

namespace robot_name {

thread_local std::mt19937 generator(std::random_device{}());
thread_local std::uniform_int_distribution<int> letter_dist(0, 25);
thread_local std::uniform_int_distribution<int> digit_dist(0, 9);

std::unordered_set<std::string> robot::_names_list;

robot::robot() {
    generate_name();
}

const std::string& robot::name() const {
    return _name;
}

void robot::generate_name() {
    constexpr int max_attempts = 1000;
    int attempts = 0;
    
    do {
        _name.clear();
        _name.reserve(5);
        
        _name += static_cast<char>('A' + letter_dist(generator));
        _name += static_cast<char>('A' + letter_dist(generator));
        _name += static_cast<char>('0' + digit_dist(generator));
        _name += static_cast<char>('0' + digit_dist(generator));
        _name += static_cast<char>('0' + digit_dist(generator));
        
        ++attempts;
    } while (_names_list.count(_name) && attempts < max_attempts);
    
    _names_list.insert(_name);
}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name