#include <string>
using namespace std;
namespace log_line {
    string message(const string& log) {
        size_t pos = log.find(' ');
        return (pos != string::npos) ? log.substr(pos + 1) : "";
    }
    string log_level(const string& log) {
        size_t end_pos = log.find(']');
        return (end_pos != string::npos && end_pos > 1) ? log.substr(1, end_pos - 1) : "";
    }
    string reformat(const string& log) {
        size_t space_pos = log.find(' ');
        size_t bracket_pos = log.find(']');
        
        if (space_pos == string::npos || bracket_pos == string::npos || bracket_pos <= 1) {
            return "";
        }
        
        string result;
        result.reserve(log.length() + 3);
        result.append(log, space_pos + 1, string::npos);
        result.append(" (");
        result.append(log, 1, bracket_pos - 1);
        result.append(")");
        
        return result;
    }
}