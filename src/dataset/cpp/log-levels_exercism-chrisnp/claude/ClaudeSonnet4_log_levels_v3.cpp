#include <string>
#include <string_view>

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
        const auto start_pos = line.find('[');
        const auto end_pos = line.find("]:");
        if (start_pos == string::npos || end_pos == string::npos || start_pos >= end_pos) {
            return {};
        }
        return line.substr(start_pos + 1, end_pos - start_pos - 1);
    }

    auto reformat(const string &line) noexcept -> string {
        const auto colon_pos = line.find(':');
        const auto start_pos = line.find('[');
        const auto end_pos = line.find("]:");
        
        if (colon_pos == string::npos || start_pos == string::npos || 
            end_pos == string::npos || colon_pos + 2 >= line.length() || 
            start_pos >= end_pos) {
            return {};
        }
        
        string result;
        const auto msg_len = line.length() - colon_pos - 2;
        const auto level_len = end_pos - start_pos - 1;
        result.reserve(msg_len + level_len + 4);
        
        result.append(line, colon_pos + 2, msg_len);
        result.append(" (");
        result.append(line, start_pos + 1, level_len);
        result.append(")");
        
        return result;
    }
   
} // namespace log_line

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif