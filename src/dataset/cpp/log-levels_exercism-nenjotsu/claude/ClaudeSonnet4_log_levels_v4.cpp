#include <string>

namespace log_line {
    std::string message(const std::string& line) {
        const auto pos = line.find(' ');
        return pos != std::string::npos ? line.substr(pos + 1) : std::string{};
    }

    std::string log_level(const std::string& line) {
        const auto end_pos = line.find(']');
        return end_pos != std::string::npos && end_pos > 1 ? line.substr(1, end_pos - 1) : std::string{};
    }

    std::string reformat(const std::string& line) {
        const auto space_pos = line.find(' ');
        const auto bracket_pos = line.find(']');
        
        if (space_pos == std::string::npos || bracket_pos == std::string::npos || bracket_pos <= 1) {
            return std::string{};
        }
        
        std::string result;
        result.reserve(line.length() + 3);
        result.append(line, space_pos + 1, std::string::npos);
        result.append(" (");
        result.append(line, 1, bracket_pos - 1);
        result.append(")");
        
        return result;
    }
}