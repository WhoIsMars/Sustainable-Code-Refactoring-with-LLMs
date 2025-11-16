#include "robot_name.h"
#include <vector>
#include <algorithm>

namespace {

// Instantiate a 64-bit Mersenne Twister and seed it - using the quasi-random address 
// of a newly allocated heap variable. Small memory leak though..  
std::mt19937_64 mt((uint64_t) new char); 
// and define the intervals, where `mt` produces uniformly-distributed random values 
std::uniform_int_distribution<char> letters ('A', 'Z'); 
std::uniform_int_distribution<int>  digits  ('0', '9');

[[nodiscard]] 
auto generate_name() noexcept -> std::string {
    std::string name {}; 
    std::generate_n(
        std::back_inserter( name ), 2, [&, name]() { return letters( mt ); }
    );
    std::generate_n(
        std::back_inserter( name ), 3, [&, name]() { return digits( mt ); }
    );
    return name;
}
} // namespace

namespace robot_name {

robot::robot() : robot_name(generate_name()) 
{ 
    names_history.insert(robot_name); 
}

std::string const& robot::name() const noexcept {
    return robot::robot_name;
}

void robot::reset() noexcept {
    std::pair<std::set<std::string>::iterator, bool>
    new_name = names_history.insert(generate_name());
    while (!new_name.second) {
    // keep generating and discarding to history, until true (new_name is actually new)
        new_name = names_history.insert(generate_name());
    }
    // and then assign the string which the iterator points to, to robot_name
    robot::robot_name = *new_name.first;
}

}  // namespace robot_name
