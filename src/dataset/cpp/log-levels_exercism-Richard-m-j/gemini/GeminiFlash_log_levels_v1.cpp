#include <string>
#include <string_view>

namespace log_line {

std::string message(std::string_view log) {
    size_t pos = log.find(' ');
    if (pos != std::string_view::npos) {
        return std::string(log.substr(pos + 1));
    }
    return std::string(log); // Or handle the case where there's no space appropriately
}

std::string log_level(std::string_view log) {
    size_t start = log.find('[') + 1;
    size_t end = log.find(']');

    if (start != std::string_view::npos && end != std::string_view::npos && end > start) {
        return std::string(log.substr(start, end - start));
    }
    return ""; // Or handle the error case appropriately
}

std::string reformat(std::string_view log) {
    std::string msg = message(log);
    std::string level = log_level(log);
    return msg + " (" + level + ")";
}

} // namespace log_line