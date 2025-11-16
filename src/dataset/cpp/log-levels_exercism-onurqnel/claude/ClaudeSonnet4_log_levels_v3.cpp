#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        const auto messageIndex = line.find(':');
        return messageIndex != std::string::npos ? line.substr(messageIndex + 2) : "";
    }

    std::string log_level(const std::string& line)
    {
        const auto levelStartIndex = line.find('[');
        const auto levelEndIndex = line.find(']');
        return (levelStartIndex != std::string::npos && levelEndIndex != std::string::npos) 
               ? line.substr(levelStartIndex + 1, levelEndIndex - levelStartIndex - 1) : "";
    }

    std::string reformat(const std::string& line)
    {
        const auto messageIndex = line.find(':');
        const auto levelStartIndex = line.find('[');
        const auto levelEndIndex = line.find(']');
        
        if (messageIndex == std::string::npos || levelStartIndex == std::string::npos || levelEndIndex == std::string::npos) {
            return "";
        }
        
        std::string result;
        result.reserve(line.length() + 3);
        result.append(line, messageIndex + 2, std::string::npos);
        result.append(" (");
        result.append(line, levelStartIndex + 1, levelEndIndex - levelStartIndex - 1);
        result.append(")");
        
        return result;
    }
}