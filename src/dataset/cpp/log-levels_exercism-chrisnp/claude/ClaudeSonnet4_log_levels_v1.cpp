#include <string>

namespace log_line {
    using string = std::string;

    [[nodiscard]]
    auto message(const string &line) noexcept -> string {
        const auto colon_pos = line.find(':');
        if (colon_pos == string::npos || colon_pos + 2 >= line.length()) {
            return {};
        }
        return line.substr(colon_pos + 2);
    }
    
    [[nodiscard]]
    auto log_level(const string &line) noexcept -> string {
        const auto bracket_start = line.find('[');
        const auto bracket_end = line.find(']');
        if (bracket_start == string::npos || bracket_end == string::npos || 
            bracket_start >= bracket_end) {
            return {};
        }
        return line.substr(bracket_start + 1, bracket_end - bracket_start - 1);
    }
    
    auto reformat(const string &line) noexcept -> string {
        const auto colon_pos = line.find(':');
        const auto bracket_start = line.find('[');
        const auto bracket_end = line.find(']');
        
        if (colon_pos == string::npos || bracket_start == string::npos || 
            bracket_end == string::npos || bracket_start >= bracket_end ||
            colon_pos + 2 >= line.length()) {
            return {};
        }
        
        string result;
        result.reserve(line.length() + 3);
        
        // Append message part
        result.append(line, colon_pos + 2, string::npos);
        result += " (";
        // Append log level part
        result.append(line, bracket_start + 1, bracket_end - bracket_start - 1);
        result += ')';
        
        return result;
    }
   
} // namespace log_line

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif