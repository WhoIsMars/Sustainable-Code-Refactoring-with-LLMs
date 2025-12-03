#include "robot_name.h"
#include <array>
#include <mutex>

namespace robot_name
{
    robot::robot() : m_robot_name(generate_name()) {}

    std::string robot::name() const { return m_robot_name; }

    void robot::reset() { m_robot_name = generate_name(); }

    std::string robot::generate_name() const
    {
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);

        static std::array<char, 2> prefix = {'A', 'A'};
        static unsigned short unit_number = 0;

        std::string name;
        name.reserve(5);
        name.push_back(prefix[0]);
        name.push_back(prefix[1]);

        char buffer[4];
        snprintf(buffer, sizeof(buffer), "%03d", unit_number);
        name += buffer;

        if (unit_number == 999) {
            next_prefix(prefix);
            unit_number = 0;
        } else {
            unit_number++;
        }

        return name;
    }

    void robot::next_prefix(std::array<char, 2>& prefix) const
    {
        constexpr std::array<char, 26> letters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

        if (prefix[1] == letters.back()) {
            if (prefix[0] == letters.back()) throw std::range_error("Prefix combinations exhausted.");
            for (size_t i = 0; i < letters.size(); ++i) {
                if (prefix[0] == letters[i]) {
                    prefix[0] = letters[i + 1];
                    break;
                }
            }
            prefix[1] = letters[0];
        } else {
            for (size_t i = 0; i < letters.size(); ++i) {
                if (prefix[1] == letters[i]) {
                    prefix[1] = letters[i + 1];
                    break;
                }
            }
        }
    }

} // namespace robot_name