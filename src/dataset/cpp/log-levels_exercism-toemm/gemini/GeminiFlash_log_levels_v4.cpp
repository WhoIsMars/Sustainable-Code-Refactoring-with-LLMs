#include <string>
#include <iostream>

namespace log_line {
    std::string message(std::string line) {
        size_t pos = line.find(" ");
        if (pos != std::string::npos) {
            return line.substr(pos + 1);
        }
        return "";
    }

    std::string log_level(std::string line) {
        size_t start = 1;
        size_t end = line.find("]");
        if (end != std::string::npos && end > start) {
            return line.substr(start, end - start);
        }
        return "";
    }

    std::string reformat(std::string line) {
        std::string msg = message(line);
        std::string level = log_level(line);
        return msg.empty() && level.empty() ? "" : msg + " (" + level + ")";
    }
}