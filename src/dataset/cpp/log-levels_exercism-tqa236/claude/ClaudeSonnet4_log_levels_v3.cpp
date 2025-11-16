#include <string>
#include <string_view>

namespace log_line
{
    std::string message(std::string line)
    {
        size_t pos = line.find(' ');
        if (pos == std::string::npos) return line;
        return line.substr(pos + 1);
    }

    std::string log_level(std::string line)
    {
        size_t pos = line.find(' ');
        if (pos == std::string::npos || pos < 2) return "";
        return line.substr(1, pos - 2);
    }

    std::string reformat(std::string line)
    {
        size_t pos = line.find(' ');
        if (pos == std::string::npos) return line;
        
        std::string result;
        result.reserve(line.length() + 3);
        
        result.append(line, pos + 1, std::string::npos);
        result.append(" (");
        if (pos >= 2) {
            result.append(line, 1, pos - 2);
        }
        result.append(")");
        
        return result;
    }
}