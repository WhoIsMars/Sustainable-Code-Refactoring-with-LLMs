#include <string>

namespace log_line
{
    std::string message(const std::string& line)
    {
        size_t pos = line.find(' ');
        return (pos != std::string::npos) ? line.substr(pos + 1) : "";
    }

    std::string log_level(const std::string& line)
    {
        size_t start = line.find('[');
        size_t end = line.find(']');
        return (start != std::string::npos && end != std::string::npos && end > start + 1) 
               ? line.substr(start + 1, end - start - 1) 
               : "";
    }

    std::string reformat(const std::string& line)
    {
        return message(line) + " (" + log_level(line) + ")";
    }
}