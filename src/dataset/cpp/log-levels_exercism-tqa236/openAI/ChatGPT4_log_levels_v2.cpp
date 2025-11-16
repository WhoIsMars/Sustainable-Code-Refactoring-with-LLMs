#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        // return the message
        size_t pos = line.find(' ');
        return line.substr(pos + 1);
    }

    std::string log_level(const std::string& line)
    {
        // return the log level
        size_t start = line.find('[') + 1;
        size_t end = line.find(']');
        return line.substr(start, end - start);
    }

    std::string reformat(const std::string& line)
    {
        // return the reformatted message
        size_t pos = line.find(' ');
        size_t start = line.find('[') + 1;
        size_t end = line.find(']');
        return line.substr(pos + 1) + " (" + line.substr(start, end - start) + ")";
    }
}