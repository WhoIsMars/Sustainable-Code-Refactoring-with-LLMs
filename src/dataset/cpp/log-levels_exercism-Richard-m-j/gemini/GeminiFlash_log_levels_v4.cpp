#include <string>
#include <string_view>

namespace log_line {

std::string message(std::string_view log) {
    size_t pos = log.find(' ');
    if (pos == std::string_view::npos) {
        return "";
    }
    return std::string(log.substr(pos + 1));
}

std::string log_level(std::string_view log) {
    size_t start = log.find('[') + 1;
    size_t end = log.find(']');

    if (start == std::string_view::npos || end == std::string_view::npos || start >= end) {
        return "";
    }

    return std::string(log.substr(start, end - start));
}

std::string reformat(std::string log) {
    std::string_view log_view = log;
    std::string msg = message(log_view);
    std::string level = log_level(log_view);

    return msg + " (" + level + ")";
}

} // namespace log_line