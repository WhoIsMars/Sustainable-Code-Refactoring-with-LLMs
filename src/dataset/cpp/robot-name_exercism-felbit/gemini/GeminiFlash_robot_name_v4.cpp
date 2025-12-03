#include "robot_name.h"
#include <random>
#include <algorithm>

namespace robot_name
{
    std::string robot::generate_name()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> distrib(0, 25);
        static std::uniform_int_distribution<> digit_distrib(0, 9);

        std::string name;
        name.reserve(5);

        name += static_cast<char>('A' + distrib(gen));
        name += static_cast<char>('A' + distrib(gen));
        name += std::to_string(digit_distrib(gen));
        name += std::to_string(digit_distrib(gen));
        name += std::to_string(digit_distrib(gen));

        return name;
    }

    robot::robot() : m_robot_name(generate_name()) {}

    std::string robot::name() const { return m_robot_name; }

    void robot::reset() { m_robot_name = generate_name(); }

} // namespace robot_name