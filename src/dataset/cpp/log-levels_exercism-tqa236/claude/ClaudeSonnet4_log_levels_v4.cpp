#include <string>
#include <string_view>

namespace log_line
{
    std::string message(std::string line)
    {
        const size_t pos = line.find(' ');
        if (pos == std::string::npos) return line;
        return line.substr(pos + 1);
    }

    std::string log_level(std::string line)
    {
        const size_t pos = line.find(' ');
        if (pos == std::string::npos || pos < 2) return "";
        
        return line.substr(1, pos - 2);
    }

    std::string reformat(std::string line)
    {
        const size_t pos = line.find(' ');
        if (pos == std::string::npos) return line;
        
        std::string result;
        const size_t msg_len = line.length() - pos - 1;
        const size_t level_len = (pos >= 2) ? pos - 2 : 0;
        result.reserve(msg_len + level_len + 4);
        
        result.append(line, pos + 1, msg_len);
        result.append(" (");
        if (level_len > 0) {
            result.append(line, 1, level_len);
        }
        result.append(")");
        
        return result;
    }
}