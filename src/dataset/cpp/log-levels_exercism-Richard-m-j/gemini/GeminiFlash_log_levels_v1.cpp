#include <string>
#include <string_view>

namespace log_line {

std::string message(std::string_view log) {
    size_t space_pos = log.find(' ');
    if (space_pos != std::string_view::npos) {
        return std::string(log.substr(space_pos + 1));
    }
    return std::string(log); // Or handle the case where there's no space appropriately
}

std::string log_level(std::string_view log) {
    size_t start_pos = 1;
    size_t end_pos = log.find(']');
    if (end_pos != std::string_view::npos && end_pos > start_pos) {
        return std::string(log.substr(start_pos, end_pos - start_pos));
    }
    return ""; // Or handle the case where ']' is not found appropriately
}

std::string reformat(std::string_view log) {
    std::string msg = message(log);
    std::string level = log_level(log);
    return msg + " (" + level + ")";
}

} // namespace log_line