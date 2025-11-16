#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        size_t messageIndex = line.find(':');
        return line.substr(messageIndex + 2);
    }

    std::string log_level(const std::string& line)
    {
        size_t levelStartIndex = line.find('[') + 1;
        size_t levelEndIndex = line.find(']');
        return line.substr(levelStartIndex, levelEndIndex - levelStartIndex);
    }

    std::string reformat(const std::string& line)
    {
        size_t messageIndex = line.find(':');
        size_t levelStartIndex = line.find('[') + 1;
        size_t levelEndIndex = line.find(']');
        return line.substr(messageIndex + 2) + " (" + line.substr(levelStartIndex, levelEndIndex - levelStartIndex) + ")";
    }
}