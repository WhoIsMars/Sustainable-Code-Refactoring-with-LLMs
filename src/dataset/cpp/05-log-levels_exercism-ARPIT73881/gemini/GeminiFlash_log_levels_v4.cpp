#include <string>
#include <string_view>

namespace log_line {

    std::string message(std::string_view msg) {
        size_t space_pos = msg.find(' ');
        if (space_pos == std::string_view::npos) {
            return "";
        }
        return std::string(msg.substr(space_pos + 1));
    }

    std::string log_level(std::string_view msg) {
        size_t start_pos = 1;
        size_t end_pos = msg.find(']');
        if (end_pos == std::string_view::npos || end_pos <= start_pos) {
            return "";
        }
        return std::string(msg.substr(start_pos, end_pos - start_pos));
    }

    std::string reformat(std::string msg) {
        std::string_view msg_view = msg;
        std::string message_str = message(msg_view);
        std::string log_level_str = log_level(msg_view);

        return message_str + " (" + log_level_str + ")";
    }
}