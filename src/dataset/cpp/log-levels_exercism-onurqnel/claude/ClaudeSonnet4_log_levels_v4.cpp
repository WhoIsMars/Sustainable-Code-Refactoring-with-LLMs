#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        const auto messageIndex = line.find(':');
        return line.substr(messageIndex + 2);
    }

    std::string log_level(const std::string& line)
    {
        const auto levelStartIndex = line.find('[');
        const auto levelEndIndex = line.find(']');
        return line.substr(levelStartIndex + 1, levelEndIndex - levelStartIndex - 1);
    }

    std::string reformat(const std::string& line)
    {
        const auto colonPos = line.find(':');
        const auto bracketStartPos = line.find('[');
        const auto bracketEndPos = line.find(']');
        
        std::string result;
        result.reserve(line.length() + 3);
        
        result.append(line, colonPos + 2, std::string::npos);
        result.append(" (");
        result.append(line, bracketStartPos + 1, bracketEndPos - bracketStartPos - 1);
        result.push_back(')');
        
        return result;
    }
}