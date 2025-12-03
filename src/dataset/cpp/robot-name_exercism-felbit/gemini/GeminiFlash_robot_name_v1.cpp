#include "robot_name.h"

#include <random>

namespace robot_name {

    robot::robot() : m_robot_name(generate_name()) {}

    std::string robot::name() const { return m_robot_name; }

    void robot::reset() { m_robot_name = generate_name(); }

    std::string robot::generate_name() const {
        static std::mt19937 generator(std::random_device{}());
        static std::uniform_int_distribution<int> letter_dist(0, 25);
        static std::uniform_int_distribution<int> number_dist(0, 999);

        std::string name;
        name.reserve(5); 

        name += static_cast<char>('A' + letter_dist(generator));
        name += static_cast<char>('A' + letter_dist(generator));

        int number = number_dist(generator);
        name += std::to_string(1000 + number).substr(1);

        return name;
    }

} // namespace robot_name