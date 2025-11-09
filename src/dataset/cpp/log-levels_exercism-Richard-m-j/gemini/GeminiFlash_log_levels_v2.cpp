#include <string>
#include <string_view>

namespace log_line {

std::string_view message(std::string_view log) {
    size_t space_pos = log.find(' ');
    if (space_pos != std::string_view::npos) {
        return log.substr(space_pos + 1);
    }
    return ""; // Or handle the case where there's no space appropriately
}

std::string_view log_level(std::string_view log) {
    size_t start_pos = 1;
    size_t end_pos = log.find(']');
    if (end_pos != std::string_view::npos && end_pos > start_pos) {
        return log.substr(start_pos, end_pos - start_pos);
    }
    return ""; // Or handle the case where ']' is not found appropriately
}

std::string reformat(std::string log) {
    std::string_view msg = message(log);
    std::string_view level = log_level(log);

    std::string result;
    result.reserve(msg.length() + level.length() + 4); // Pre-allocate memory

    result.append(msg);
    result.append(" (");
    result.append(level);
    result.append(")");

    return result;
}

} // namespace log_line