#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        return line.substr(line.find(":") + 2);
    }

    std::string log_level(const std::string& line)
    {
        auto levelStartIndex = line.find("[") + 1;
        auto levelLength = line.find("]") - levelStartIndex;
        return line.substr(levelStartIndex, levelLength);
    }

    std::string reformat(const std::string& line)
    {
        return message(line) + " (" + log_level(line) + ")";
    }
}