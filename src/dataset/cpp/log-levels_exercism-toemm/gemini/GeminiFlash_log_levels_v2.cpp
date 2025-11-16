#include <string>
#include <iostream>
#include <string_view>

namespace log_line {
    std::string message(std::string_view line) {
        size_t space_pos = line.find(" ");
        if (space_pos == std::string_view::npos) {
            return ""; // Or handle the error as appropriate
        }
        return std::string(line.substr(space_pos + 1));
    }

    std::string log_level(std::string_view line) {
        size_t start_pos = 1;
        size_t end_pos = line.find("]");
        if (end_pos == std::string_view::npos || end_pos <= start_pos) {
            return ""; // Or handle the error as appropriate
        }
        return std::string(line.substr(start_pos, end_pos - start_pos));
    }

    std::string reformat(std::string line) {
        std::string_view line_view = line;
        return message(line_view) + " (" + log_level(line_view) + ")";
    }
}