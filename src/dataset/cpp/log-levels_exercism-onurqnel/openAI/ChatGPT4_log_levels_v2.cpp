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
        auto levelEndIndex = line.find("]");
        return line.substr(levelStartIndex, levelEndIndex - levelStartIndex);
    }

    std::string reformat(const std::string& line)
    {
        auto msg = message(line);
        auto level = log_level(line);
        return msg + " (" + level + ")";
    }
}