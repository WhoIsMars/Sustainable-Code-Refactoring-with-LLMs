#include <string>
#include <string_view>

namespace log_line {
    std::string message(std::string line) {
        std::string_view sv(line);
        auto pos = sv.find(' ');
        if (pos == std::string_view::npos) return line;
        return std::string(sv.substr(pos + 1));
    }

    std::string log_level(std::string line) {
        std::string_view sv(line);
        if (sv.empty() || sv[0] != '[') return {};
        auto pos = sv.find(']');
        if (pos == std::string_view::npos || pos <= 1) return {};
        return std::string(sv.substr(1, pos - 1));
    }

    std::string reformat(std::string line) {
        std::string_view sv(line);
        
        auto space_pos = sv.find(' ');
        if (space_pos == std::string_view::npos) return line;
        
        if (sv.empty() || sv[0] != '[') return line;
        auto bracket_pos = sv.find(']');
        if (bracket_pos == std::string_view::npos || bracket_pos <= 1) return line;
        
        std::string result;
        result.reserve(line.length() + 3);
        result.append(sv.substr(space_pos + 1));
        result.append(" (");
        result.append(sv.substr(1, bracket_pos - 1));
        result.append(")");
        
        return result;
    }
}