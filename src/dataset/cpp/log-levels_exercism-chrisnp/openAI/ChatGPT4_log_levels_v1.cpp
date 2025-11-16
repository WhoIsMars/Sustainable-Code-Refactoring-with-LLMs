#include <string>

namespace log_line {
    using string = std::string;

    [[nodiscard]]
    auto message(const string &line) noexcept -> string {
        return line.substr(line.find(':') + 2);
    }

    [[nodiscard]]
    auto log_level(const string &line) noexcept -> string {
        auto start = line.find('[') + 1;
        auto length = line.find("]:") - start;
        return line.substr(start, length);
    }

    auto reformat(const string &line) noexcept -> string {
        return line.substr(line.find(':') + 2) + " (" + log_level(line) + ")";
    }

} // namespace log_line


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif