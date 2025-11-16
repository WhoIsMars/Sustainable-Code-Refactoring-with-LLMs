#include <string>
#include <string_view>

namespace log_line
{
    std::string message(std::string_view line)
    {
        size_t messageIndex = line.find(":");
        return std::string(line.substr(messageIndex + 2));
    }

    std::string log_level(std::string_view line)
    {
        size_t levelStartIndex = line.find("[");
        size_t levelEndIndex = line.find("]");
        return std::string(line.substr(levelStartIndex + 1, levelEndIndex - levelStartIndex - 1));
    }

    std::string reformat(std::string_view line)
    {
        std::string msg = message(line);
        std::string level = log_level(line);
        return msg + " (" + level + ")";
    }
}