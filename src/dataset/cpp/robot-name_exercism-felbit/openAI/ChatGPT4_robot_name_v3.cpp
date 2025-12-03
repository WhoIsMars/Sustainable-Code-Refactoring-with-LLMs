#include "robot_name.h"
#include <array>

namespace robot_name
{
    robot::robot() : m_robot_name(generate_name()) {}

    std::string robot::name() const { return m_robot_name; }

    void robot::reset() { m_robot_name = generate_name(); }

    std::string robot::generate_name() const
    {
        static std::array<char, 26> letters {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        static char prefix1 = 'A';
        static char prefix2 = 'A';
        static unsigned short unit_number = 0;

        std::string name = {prefix1, prefix2};
        name += std::to_string(1000 + unit_number).substr(1);

        if (++unit_number > 999) {
            unit_number = 0;
            if (++prefix2 > 'Z') {
                prefix2 = 'A';
                if (++prefix1 > 'Z') throw std::range_error("Prefix combinations exhausted.");
            }
        }

        return name;
    }

    std::string robot::next_prefix(const std::string& prefix) const
    {
        if (prefix.size() != 2) throw std::invalid_argument("Invalid prefix size.");
        char first = prefix[0];
        char second = prefix[1];

        if (++second > 'Z') {
            second = 'A';
            if (++first > 'Z') throw std::range_error("Prefix combinations exhausted.");
        }

        return {first, second};
    }

} // namespace robot_name