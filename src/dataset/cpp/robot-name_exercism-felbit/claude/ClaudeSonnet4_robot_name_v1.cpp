#include "robot_name.h"

namespace robot_name
{
    robot::robot() : m_robot_name(generate_name()) {}

    std::string robot::name() const { return m_robot_name; }

    void robot::reset() { m_robot_name = generate_name(); }

    std::string robot::generate_name() const
    {
        static char prefix[3] = {'A', 'A', '\0'};
        static unsigned short unit_number = 0;

        std::string name;
        name.reserve(5);
        name += prefix[0];
        name += prefix[1];
        
        if (unit_number < 10) {
            name += "00";
            name += ('0' + unit_number);
        } else if (unit_number < 100) {
            name += '0';
            name += ('0' + unit_number / 10);
            name += ('0' + unit_number % 10);
        } else {
            name += ('0' + unit_number / 100);
            name += ('0' + (unit_number / 10) % 10);
            name += ('0' + unit_number % 10);
        }

        if (unit_number == 999) {
            next_prefix(prefix);
            unit_number = 0;
        } else {
            unit_number++;
        }

        return name;
    }

    std::string robot::next_prefix(const std::string& prefix) const
    {
        std::string tmp = prefix;
        
        if (prefix[1] == 'Z') {
            if (prefix[0] == 'Z') throw std::range_error("Prefix combinations exhausted.");
            tmp[0] = prefix[0] + 1;
            tmp[1] = 'A';
        } else {
            tmp[1] = prefix[1] + 1;
        }

        return tmp;
    }

    void robot::next_prefix(char* prefix) const
    {
        if (prefix[1] == 'Z') {
            if (prefix[0] == 'Z') throw std::range_error("Prefix combinations exhausted.");
            prefix[0]++;
            prefix[1] = 'A';
        } else {
            prefix[1]++;
        }
    }

} // namespace robot_name