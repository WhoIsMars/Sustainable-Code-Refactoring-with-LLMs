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
        size_t levelStartIndex = line.find('[');
        size_t levelEndIndex = line.find(']');
        return line.substr(levelStartIndex + 1, levelEndIndex - levelStartIndex - 1);
    }

    std::string reformat(const std::string& line)
    {
        size_t colonIndex = line.find(':');
        size_t levelStartIndex = line.find('[');
        size_t levelEndIndex = line.find(']');
        
        std::string result;
        result.reserve(line.length() + 3);
        
        result.append(line, colonIndex + 2, std::string::npos);
        result.append(" (");
        result.append(line, levelStartIndex + 1, levelEndIndex - levelStartIndex - 1);
        result.append(")");
        
        return result;
    }
}