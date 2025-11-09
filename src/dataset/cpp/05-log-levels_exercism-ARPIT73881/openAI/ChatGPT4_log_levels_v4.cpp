#include <string>

namespace log_line {
    std::string message(const std::string& msg) {
        return msg.substr(msg.find(' ') + 1);
    }
    std::string log_level(const std::string& msg) {
        auto end = msg.find(']');
        return msg.substr(1, end - 1);
    }
    std::string reformat(const std::string& msg) {
        auto start = msg.find(' ') + 1;
        auto end = msg.find(']');
        return msg.substr(start) + " (" + msg.substr(1, end - 1) + ")";
    }
}