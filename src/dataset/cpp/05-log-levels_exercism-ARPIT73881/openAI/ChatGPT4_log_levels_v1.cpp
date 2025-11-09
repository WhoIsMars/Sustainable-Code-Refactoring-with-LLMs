#include <string>

namespace log_line {
    std::string message(const std::string& msg) {
        return msg.substr(msg.find(' ') + 1);
    }
    std::string log_level(const std::string& msg) {
        auto start = msg.find('[') + 1;
        auto end = msg.find(']');
        return msg.substr(start, end - start);
    }
    std::string reformat(const std::string& msg) {
        auto start = msg.find('[') + 1;
        auto end = msg.find(']');
        return msg.substr(msg.find(' ') + 1) + " (" + msg.substr(start, end - start) + ")";
    }
}