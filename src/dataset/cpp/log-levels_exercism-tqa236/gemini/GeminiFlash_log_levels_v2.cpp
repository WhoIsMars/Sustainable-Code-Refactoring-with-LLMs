#include <string>
#include <string_view>

namespace log_line
{
    std::string message(std::string_view line)
    {
        size_t pos = line.find(' ');
        return std::string(line.substr(pos + 1));
    }

    std::string log_level(std::string_view line)
    {
        size_t pos = line.find(' ');
        if (pos == std::string_view::npos || pos < 3)
        {
            return "";
        }
        return std::string(line.substr(1, pos - 2));
    }

    std::string reformat(std::string_view line)
    {
        std::string msg = message(line);
        std::string level = log_level(line);
        return msg + " (" + level + ")";
    }
}