#include <string>
#include <string_view>

namespace log_line {

    std::string message(std::string_view msg) {
        size_t pos = msg.find(" ");
        if (pos == std::string_view::npos) {
            return ""; // Or handle the error as appropriate
        }
        return std::string(msg.substr(pos + 1));
    }

    std::string log_level(std::string_view msg) {
        size_t start = 1;
        size_t end = msg.find("]");
        if (end == std::string_view::npos || end <= start) {
            return ""; // Or handle the error as appropriate
        }
        return std::string(msg.substr(start, end - start));
    }

    std::string reformat(std::string msg) {
        std::string_view msg_view = msg;
        return message(msg_view) + " (" + log_level(msg_view) + ")";
    }
}