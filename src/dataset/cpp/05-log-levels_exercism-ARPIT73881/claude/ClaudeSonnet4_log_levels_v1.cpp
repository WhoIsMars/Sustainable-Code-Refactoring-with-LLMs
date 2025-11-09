#include <string>

namespace log_line {
    std::string message(std::string msg) {
        size_t pos = msg.find(' ');
        return pos != std::string::npos ? msg.substr(pos + 1) : "";
    }
    
    std::string log_level(std::string msg) {
        size_t end_pos = msg.find(']');
        return end_pos != std::string::npos && end_pos > 1 ? msg.substr(1, end_pos - 1) : "";
    }
    
    std::string reformat(std::string msg) {
        size_t space_pos = msg.find(' ');
        size_t bracket_pos = msg.find(']');
        
        if (space_pos == std::string::npos || bracket_pos == std::string::npos || bracket_pos <= 1) {
            return "";
        }
        
        std::string result;
        result.reserve(msg.length() + 3);
        result.append(msg, space_pos + 1, std::string::npos);
        result.append(" (");
        result.append(msg, 1, bracket_pos - 1);
        result.append(")");
        
        return result;
    }
}