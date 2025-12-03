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

        char name_buffer[6];
        name_buffer[0] = prefix[0];
        name_buffer[1] = prefix[1];
        name_buffer[2] = '0' + (unit_number / 100);
        name_buffer[3] = '0' + ((unit_number / 10) % 10);
        name_buffer[4] = '0' + (unit_number % 10);
        name_buffer[5] = '\0';

        if (unit_number == 999) {
            next_prefix(prefix);
            unit_number = 0;
        } else {
            unit_number++;
        }

        return std::string(name_buffer);
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

    std::string robot::next_prefix(const std::string& prefix) const
    {
        std::string tmp = prefix;
        const std::string letters {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

        if (prefix[1] == letters.back()) {
            if (prefix[0] == letters.back()) throw std::range_error("Prefix combinations exhausted.");
            tmp[0] = letters[letters.find(tmp[0]) + 1];
            tmp[1] = letters[0];
        } else {
            tmp[1] = letters[letters.find(tmp[1]) + 1];
        }

        return tmp;
    }

} // namespace robot_name