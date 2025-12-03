#include <string>
#include <string_view>

namespace log_line
{
    std::string message(std::string line)
    {
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            return line.substr(pos + 1);
        }
        return "";
    }

    std::string log_level(std::string line)
    {
        size_t pos = line.find(' ');
        if (pos != std::string::npos && pos > 2)
        {
            return line.substr(1, pos - 2);
        }
        return "";
    }

    std::string reformat(std::string line)
    {
        std::string level = log_level(line);
        std::string msg = message(line);
        return msg.empty() ? "" : msg + " (" + level + ")";
    }
}