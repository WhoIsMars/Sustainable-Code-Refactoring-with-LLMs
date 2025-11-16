#include <string>

namespace log_line
{
    std::string message(std::string line)
    {
        // return the message
        std::string delimiter = " ";
        size_t pos = line.find(delimiter);
        return line.substr(pos + delimiter.length());
    }

    std::string log_level(std::string line)
    {
        // return the log level
        std::string delimiter = " ";
        size_t pos = line.find(delimiter);
        std::string before = line.substr(0, pos);
        if (before.length() > 1)
        {
            before = before.substr(1, before.length() - 3);
        }
        else
        {
            before = "";
        }
        return before;
    }

    std::string reformat(std::string line)
    {
        // return the reformatted message
        return message(line) + " (" + log_level(line) + ")";
    }
}
