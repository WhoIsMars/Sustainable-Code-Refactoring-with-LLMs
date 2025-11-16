#include "robot_name.h"

#include <string>
#include <unordered_set>
#include <random>
#include <mutex>

namespace robot_name {

namespace {
    std::unordered_set<std::string> _names_list;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);
    std::mutex name_mutex;

    std::string generate_unique_name() {
        std::string name;
        do {
            name = std::string{
                static_cast<char>('A' + letter_dist(rng)),
                static_cast<char>('A' + letter_dist(rng)),
                static_cast<char>('0' + digit_dist(rng)),
                static_cast<char>('0' + digit_dist(rng)),
                static_cast<char>('0' + digit_dist(rng))
            };
        } while (!_names_list.insert(name).second);
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
    std::lock_guard<std::mutex> lock(name_mutex);
    _name = generate_unique_name();
}

void robot::reset() {
    generate_name();
}

}  // namespace robot_name