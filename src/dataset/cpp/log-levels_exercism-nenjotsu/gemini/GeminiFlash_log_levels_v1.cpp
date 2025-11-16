#include <string>
#include <string_view>

namespace log_line {
    std::string message(std::string line) {
        size_t pos = line.find(" ");
        if (pos != std::string::npos) {
            return line.substr(pos + 1);
        }
        return ""; // Or handle the case where there's no space appropriately
    }

    std::string log_level(std::string line) {
        size_t start = 1;
        size_t end = line.find("]");
        if (end != std::string::npos && end > start) {
            return line.substr(start, end - start);
        }
        return ""; // Or handle the case where ']' is not found appropriately
    }

    std::string reformat(std::string line) {
        std::string msg = message(line);
        std::string level = log_level(line);
        return msg + " (" + level + ")";
    }
}