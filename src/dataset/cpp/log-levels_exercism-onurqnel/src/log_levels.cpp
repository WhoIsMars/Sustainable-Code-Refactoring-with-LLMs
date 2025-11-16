#include <string>

namespace log_line
{
    std::string message(std::string line)
    {
        int messageIndex = line.find(":");
        return line.substr(messageIndex+2);
    }

    std::string log_level(std::string line)
    {
        int levelStartIndex = line.find("[");
        int levelEndIndex = line.find("]");
        return line.substr(levelStartIndex + 1, levelEndIndex - 1);
    }

    std::string reformat(std::string line)
    {
        return message(line) + " (" + log_level(line) + ")";
    }
}
