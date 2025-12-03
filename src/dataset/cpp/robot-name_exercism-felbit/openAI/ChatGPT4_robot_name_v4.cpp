#include "robot_name.h"
#include <array>

namespace robot_name
{
    robot::robot() : m_robot_name(generate_name()) {}

    std::string robot::name() const { return m_robot_name; }

    void robot::reset() { m_robot_name = generate_name(); }

    std::string robot::generate_name() const
    {
        static std::array<char, 2> prefix = {'A', 'A'};
        static unsigned short unit_number = 0;

        char name[6];
        name[0] = prefix[0];
        name[1] = prefix[1];
        name[2] = '0' + (unit_number / 100);
        name[3] = '0' + ((unit_number / 10) % 10);
        name[4] = '0' + (unit_number % 10);
        name[5] = '\0';

        if (++unit_number > 999) {
            unit_number = 0;
            if (++prefix[1] > 'Z') {
                prefix[1] = 'A';
                if (++prefix[0] > 'Z') {
                    throw std::range_error("Prefix combinations exhausted.");
                }
            }
        }

        return std::string(name);
    }

    std::string robot::next_prefix(const std::string& prefix) const
    {
        throw std::logic_error("next_prefix should not be called directly.");
    }

} // namespace robot_name