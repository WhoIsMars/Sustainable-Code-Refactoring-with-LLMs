#include <string>
#include <string_view>

namespace log_line
{
    std::string message(std::string_view line)
    {
        size_t pos = line.find(' ');
        if (pos != std::string_view::npos) {
            return std::string(line.substr(pos + 1));
        }
        return "";
    }

    std::string log_level(std::string_view line)
    {
        size_t pos = line.find(' ');
        if (pos != std::string_view::npos) {
            std::string_view before = line.substr(0, pos);
            if (before.length() > 1)
            {
                return std::string(before.substr(1, before.length() - 2));
            }
        }
        return "";
    }

    std::string reformat(std::string line)
    {
        std::string msg = message(line);
        std::string level = log_level(line);
        return msg + " (" + level + ")";
    }
}