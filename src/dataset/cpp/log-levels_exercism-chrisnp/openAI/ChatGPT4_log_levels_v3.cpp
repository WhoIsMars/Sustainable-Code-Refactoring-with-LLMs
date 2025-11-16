#include <string>
#include <string_view>

namespace log_line {
    using string = std::string;
    using string_view = std::string_view;

    [[nodiscard]]
    auto message(const string &line) noexcept -> string {
        auto msg_start = line.find(':') + 2;
        return string(line.data() + msg_start, line.size() - msg_start);
    }

    [[nodiscard]]
    auto log_level(const string &line) noexcept -> string {
        auto log_level_start = line.find('[') + 1;
        auto log_level_end = line.find(']');
        return string(line.data() + log_level_start, log_level_end - log_level_start);
    }

    auto reformat(const string &line) noexcept -> string {
        return message(line) + " (" + log_level(line) + ")";
    }

} // namespace log_line

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif