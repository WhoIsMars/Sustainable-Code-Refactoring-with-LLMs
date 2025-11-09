#include <string>
#include <string_view>

namespace log_line {

    std::string_view message(std::string_view msg) {
        size_t space_pos = msg.find(' ');
        if (space_pos == std::string_view::npos) {
            return ""; // Or handle the case where there's no space appropriately
        }
        return msg.substr(space_pos + 1);
    }

    std::string_view log_level(std::string_view msg) {
        size_t start_pos = 1;
        size_t end_pos = msg.find(']');
        if (end_pos == std::string_view::npos || end_pos <= start_pos) {
            return ""; // Or handle the case where there's no closing bracket or it's invalid
        }
        return msg.substr(start_pos, end_pos - start_pos);
    }

    std::string reformat(std::string_view msg) {
        std::string_view lvl = log_level(msg);
        std::string_view text = message(msg);

        std::string result;
        result.reserve(text.length() + lvl.length() + 4); // Pre-allocate memory
        result.append(text);
        result.append(" (");
        result.append(lvl);
        result.append(")");
        return result;
    }
}