#include <string>
#include <iostream>
#include <string_view>

namespace log_line {
    std::string message(std::string_view line) {
        size_t pos = line.find(" ");
        if (pos == std::string_view::npos) {
            return "";
        }
        return std::string(line.substr(pos + 1));
    }

    std::string log_level(std::string_view line) {
        size_t start = 1;
        size_t end = line.find("]");
        if (end == std::string_view::npos || end <= start) {
            return "";
        }
        return std::string(line.substr(start, end - start));
    }

    std::string reformat(std::string_view line) {
        std::string msg = message(line);
        std::string level = log_level(line);
        return msg + " (" + level + ")";
    }
}