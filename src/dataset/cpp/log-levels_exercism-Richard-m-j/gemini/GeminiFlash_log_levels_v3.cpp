#include <string>
#include <string_view>

using namespace std;

namespace log_line {

    string message(string_view log) {
        size_t space_pos = log.find(' ');
        if (space_pos != string_view::npos) {
            return string(log.substr(space_pos + 1));
        }
        return "";
    }

    string log_level(string_view log) {
        size_t start_pos = 1;
        size_t end_pos = log.find(']');
        if (end_pos != string_view::npos && end_pos > start_pos) {
            return string(log.substr(start_pos, end_pos - start_pos));
        }
        return "";
    }

    string reformat(string log) {
        string_view log_view = log;
        string msg = message(log_view);
        string level = log_level(log_view);
        return msg + " (" + level + ")";
    }
} // namespace log_line