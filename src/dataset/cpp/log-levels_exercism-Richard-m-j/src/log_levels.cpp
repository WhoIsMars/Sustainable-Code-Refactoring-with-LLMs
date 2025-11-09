#include <string>
using namespace std;
namespace log_line {
    string message(string log) {
        return log.substr(log.find(" ") + 1);
    }
    string log_level(string log) {
        return log.substr(1, log.find("]") - 1);
    }
    string reformat(string log) {
        return log_line::message(log) + " (" + log_line::log_level(log) + ")";
    }
} // namespace log_line
