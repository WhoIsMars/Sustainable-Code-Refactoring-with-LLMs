#include <string>
using namespace std;
namespace log_line {
    string message(const string& log) {
        size_t pos = log.find(' ');
        return log.substr(pos + 1);
    }
    string log_level(const string& log) {
        size_t start = 1;
        size_t end = log.find(']');
        return log.substr(start, end - start);
    }
    string reformat(const string& log) {
        size_t pos = log.find(' ');
        size_t start = 1;
        size_t end = log.find(']');
        return log.substr(pos + 1) + " (" + log.substr(start, end - start) + ")";
    }
} // namespace log_line