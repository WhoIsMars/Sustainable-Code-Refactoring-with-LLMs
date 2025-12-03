#include "robot_name.h"

#include <random>
#include <algorithm>

namespace robot_name
{
    robot::robot() : m_robot_name(generate_name()) {}

    std::string robot::name() const { return m_robot_name; }

    void robot::reset() { m_robot_name = generate_name(); }

    std::string robot::generate_name() const
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 25);
        static std::uniform_int_distribution<> digit_dis(0, 9);

        std::string name;
        name.reserve(5);

        name += 'A' + dis(gen);
        name += 'A' + dis(gen);
        name += std::to_string(digit_dis(gen));
        name += std::to_string(digit_dis(gen));
        name += std::to_string(digit_dis(gen));

        return name;
    }
} // namespace robot_name