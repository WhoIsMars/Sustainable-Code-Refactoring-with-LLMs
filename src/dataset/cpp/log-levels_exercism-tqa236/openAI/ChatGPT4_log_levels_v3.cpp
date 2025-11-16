#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        return line.substr(line.find(' ') + 1);
    }

    std::string log_level(const std::string& line)
    {
        size_t start = 1;
        size_t end = line.find(']') - 1;
        return line.substr(start, end - start + 1);
    }

    std::string reformat(const std::string& line)
    {
        return message(line) + " (" + log_level(line) + ")";
    }
}