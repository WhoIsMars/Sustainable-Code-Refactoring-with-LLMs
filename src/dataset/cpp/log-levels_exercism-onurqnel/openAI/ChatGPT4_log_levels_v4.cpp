#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        return line.substr(line.find(':') + 2);
    }

    std::string log_level(const std::string& line)
    {
        size_t levelStartIndex = line.find('[') + 1;
        size_t levelEndIndex = line.find(']');
        return line.substr(levelStartIndex, levelEndIndex - levelStartIndex);
    }

    std::string reformat(const std::string& line)
    {
        size_t messageIndex = line.find(':') + 2;
        size_t levelStartIndex = line.find('[') + 1;
        size_t levelEndIndex = line.find(']');
        return line.substr(messageIndex) + " (" + line.substr(levelStartIndex, levelEndIndex - levelStartIndex) + ")";
    }
}