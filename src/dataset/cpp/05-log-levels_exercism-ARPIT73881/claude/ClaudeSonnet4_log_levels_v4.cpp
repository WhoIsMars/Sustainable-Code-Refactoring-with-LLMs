#include <string>
#include <string_view>

namespace log_line {
    std::string message(const std::string& msg) {
        const auto space_pos = msg.find(' ');
        return space_pos != std::string::npos ? msg.substr(space_pos + 1) : std::string{};
    }
    
    std::string log_level(const std::string& msg) {
        const auto bracket_pos = msg.find(']');
        return bracket_pos != std::string::npos && bracket_pos > 1 ? 
               msg.substr(1, bracket_pos - 1) : std::string{};
    }
    
    std::string reformat(const std::string& msg) {
        const auto space_pos = msg.find(' ');
        const auto bracket_pos = msg.find(']');
        
        if (space_pos == std::string::npos || bracket_pos == std::string::npos || bracket_pos <= 1) {
            return std::string{};
        }
        
        std::string result;
        const auto msg_part_size = msg.size() - space_pos - 1;
        const auto level_part_size = bracket_pos - 1;
        result.reserve(msg_part_size + level_part_size + 3);
        
        result.append(msg, space_pos + 1, msg_part_size);
        result.append(" (");
        result.append(msg, 1, level_part_size);
        result.push_back(')');
        
        return result;
    }
}