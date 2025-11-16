#include <string>

namespace log_line
{
    std::string message(std::string line)
    {
        size_t pos = line.find(' ');
        return line.substr(pos + 1);
    }

    std::string log_level(std::string line)
    {
        size_t pos = line.find(' ');
        if (pos > 2)
        {
            return line.substr(1, pos - 2);
        }
        return "";
    }

    std::string reformat(std::string line)
    {
        size_t pos = line.find(' ');
        std::string msg = line.substr(pos + 1);
        std::string level = (pos > 2) ? line.substr(1, pos - 2) : "";
        return msg + " (" + level + ")";
    }
}