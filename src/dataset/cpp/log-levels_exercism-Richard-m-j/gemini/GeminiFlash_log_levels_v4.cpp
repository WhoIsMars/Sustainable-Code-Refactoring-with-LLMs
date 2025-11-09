#include <string>
#include <string_view>
using namespace std;
namespace log_line {
    string message(string log) {
        size_t pos = log.find(" ");
        if (pos == string::npos) {
            return "";
        }
        return log.substr(pos + 1);
    }
    string log_level(string log) {
        size_t start = 1;
        size_t end = log.find("]");
        if (end == string::npos || end <= start) {
            return "";
        }
        return log.substr(start, end - start);
    }
    string reformat(string log) {
        string msg = message(log);
        string level = log_level(log);
        return msg + " (" + level + ")";
    }
} // namespace log_line