#include <string>
#include <string_view>

namespace log_line {
    std::string message(std::string msg) {
        std::string_view sv(msg);
        auto pos = sv.find(' ');
        if (pos == std::string_view::npos) return msg;
        return std::string(sv.substr(pos + 1));
    }
    
    std::string log_level(std::string msg) {
        std::string_view sv(msg);
        if (sv.empty() || sv[0] != '[') return std::string();
        auto pos = sv.find(']');
        if (pos == std::string_view::npos || pos <= 1) return std::string();
        return std::string(sv.substr(1, pos - 1));
    }
    
    std::string reformat(std::string msg) {
        std::string_view sv(msg);
        
        auto space_pos = sv.find(' ');
        if (space_pos == std::string_view::npos) return msg;
        
        if (sv.empty() || sv[0] != '[') return msg;
        auto bracket_pos = sv.find(']');
        if (bracket_pos == std::string_view::npos || bracket_pos <= 1) return msg;
        
        std::string result;
        result.reserve(msg.length() + 3);
        result.append(sv.substr(space_pos + 1));
        result.append(" (");
        result.append(sv.substr(1, bracket_pos - 1));
        result.append(")");
        
        return result;
    }
}