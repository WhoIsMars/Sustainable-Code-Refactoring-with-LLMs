#include <string>
#include <iostream>

namespace log_line {
    std::string message(const std::string& line) {
        return line.substr(line.find(' ') + 1);
    }

    std::string log_level(const std::string& line) {
        size_t start = 1;
        size_t end = line.find(']');
        return line.substr(start, end - start);
    }

    std::string reformat(const std::string& line) {
        size_t space_pos = line.find(' ');
        size_t bracket_end = line.find(']');
        return line.substr(space_pos + 1) + " (" + line.substr(1, bracket_end - 1) + ")";
    }
}