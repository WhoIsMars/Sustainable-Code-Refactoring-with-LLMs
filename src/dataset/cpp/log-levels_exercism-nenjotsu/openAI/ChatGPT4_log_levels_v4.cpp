#include <string>
#include <string_view>

namespace log_line {
    std::string message(const std::string& line) {
        auto pos = line.find(' ');
        return pos != std::string::npos ? line.substr(pos + 1) : "";
    }

    std::string log_level(const std::string& line) {
        auto start = line.find('[') + 1;
        auto end = line.find(']');
        return (start != std::string::npos && end != std::string::npos && start < end) 
               ? line.substr(start, end - start) 
               : "";
    }

    std::string reformat(const std::string& line) {
        auto pos = line.find(' ');
        auto start = line.find('[') + 1;
        auto end = line.find(']');
        if (pos != std::string::npos && start != std::string::npos && end != std::string::npos && start < end) {
            return line.substr(pos + 1) + " (" + line.substr(start, end - start) + ")";
        }
        return "";
    }
}