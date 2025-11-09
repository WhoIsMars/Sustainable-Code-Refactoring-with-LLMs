#include <string>
#include <string_view>

namespace log_line {
    std::string message(const std::string& msg) {
        auto pos = msg.find(' ');
        return pos != std::string::npos ? msg.substr(pos + 1) : "";
    }
    std::string log_level(const std::string& msg) {
        auto start = msg.find('[') + 1;
        auto end = msg.find(']');
        return (start != std::string::npos && end != std::string::npos && start < end) ? msg.substr(start, end - start) : "";
    }
    std::string reformat(const std::string& msg) {
        auto pos = msg.find(' ');
        auto start = msg.find('[') + 1;
        auto end = msg.find(']');
        if (pos != std::string::npos && start != std::string::npos && end != std::string::npos && start < end) {
            return msg.substr(pos + 1) + " (" + msg.substr(start, end - start) + ")";
        }
        return "";
    }
}