#include <string>
#include <string_view>

namespace log_line {
    using string = std::string;

    [[nodiscard]]
    auto message(const string &line) noexcept -> string {
        size_t msg_start = line.find(':');
        if (msg_start == string::npos) {
            return "";
        }
        msg_start += 2;
        return line.substr(msg_start);
    }
    [[nodiscard]]
    auto log_level(const string &line) noexcept -> string {
        size_t log_level_start = line.find('[');
        if (log_level_start == string::npos) {
            return "";
        }
        log_level_start += 1;
        size_t log_level_end = line.find("]:");
        if (log_level_end == string::npos || log_level_end <= log_level_start) {
            return "";
        }
        size_t len = log_level_end - log_level_start;
        return line.substr(log_level_start, len);
    }
    auto reformat(const string &line) noexcept -> string {
        string level = "(" + log_level(line) + ")";
        return message(line) + " " + level;
    }
   
} // namespace log_line


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif