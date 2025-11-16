#include <string>
#include <iostream>

namespace log_line {
    std::string message(const std::string& line) {
        size_t pos = line.find(' ');
        if (pos == std::string::npos) return "";
        return line.substr(pos + 1);
    }

    std::string log_level(const std::string& line) {
        if (line.empty() || line[0] != '[') return "";
        size_t end_pos = line.find(']');
        if (end_pos == std::string::npos || end_pos <= 1) return "";
        return line.substr(1, end_pos - 1);
    }

    std::string reformat(const std::string& line) {
        size_t space_pos = line.find(' ');
        size_t bracket_pos = line.find(']');
        
        if (space_pos == std::string::npos || bracket_pos == std::string::npos || 
            line.empty() || line[0] != '[' || bracket_pos <= 1) {
            return "";
        }
        
        std::string result;
        result.reserve(line.length() + 4);
        result.append(line, space_pos + 1, std::string::npos);
        result.append(" (");
        result.append(line, 1, bracket_pos - 1);
        result.append(")");
        
        return result;
    }
}