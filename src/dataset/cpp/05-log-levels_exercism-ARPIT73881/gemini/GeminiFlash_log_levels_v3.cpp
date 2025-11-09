#include <string>
#include <string_view>

namespace log_line {

    std::string message(std::string_view msg) {
        size_t space_pos = msg.find(" ");
        if (space_pos != std::string_view::npos) {
            return std::string(msg.substr(space_pos + 1));
        }
        return "";
    }

    std::string log_level(std::string_view msg) {
        if (msg.length() > 2 && msg[0] == '[') {
            size_t closing_bracket_pos = msg.find("]");
            if (closing_bracket_pos != std::string_view::npos && closing_bracket_pos > 1) {
                return std::string(msg.substr(1, closing_bracket_pos - 1));
            }
        }
        return "";
    }

    std::string reformat(std::string msg) {
        std::string_view msg_view = msg;
        std::string message_str = message(msg_view);
        std::string log_level_str = log_level(msg_view);

        return message_str + " (" + log_level_str + ")";
    }
}