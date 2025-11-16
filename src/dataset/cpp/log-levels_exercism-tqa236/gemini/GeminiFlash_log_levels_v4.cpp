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
        if (pos != std::string::npos) {
            std::string_view level_view = std::string_view(line).substr(1, pos - 2);
            return std::string(level_view);
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