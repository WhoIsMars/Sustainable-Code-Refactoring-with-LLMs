#include <string>
#include <string_view>

namespace log_line {
    std::string message(std::string_view line) {
        auto pos = line.find(' ');
        return std::string(line.substr(pos + 1));
    }

    std::string log_level(std::string_view line) {
        auto start = line.find('[') + 1;
        auto end = line.find(']');
        return std::string(line.substr(start, end - start));
    }

    std::string reformat(std::string_view line) {
        auto pos = line.find(' ');
        auto start = line.find('[') + 1;
        auto end = line.find(']');
        return std::string(line.substr(pos + 1)) + " (" + std::string(line.substr(start, end - start)) + ")";
    }
}