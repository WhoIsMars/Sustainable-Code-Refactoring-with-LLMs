#include <string>
#include <string_view>

namespace log_line {
    std::string message(std::string line) {
        size_t space_pos = line.find(" ");
        if (space_pos == std::string::npos) {
            return "";
        }
        return line.substr(space_pos + 1);
    }

    std::string log_level(std::string line) {
        size_t bracket_pos = line.find("]");
        if (bracket_pos == std::string::npos || bracket_pos <= 1) {
            return "";
        }
        return line.substr(1, bracket_pos - 1);
    }

    std::string reformat(std::string line) {
        std::string msg = message(line);
        std::string level = log_level(line);
        return msg + " (" + level + ")";
    }
}