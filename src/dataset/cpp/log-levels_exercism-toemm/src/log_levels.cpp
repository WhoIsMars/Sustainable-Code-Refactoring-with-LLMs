#include <string>
#include <iostream>

namespace log_line {
    std::string message(std::string line) {

        std::string formLine = line.substr(line.find(" ")+1);
        return formLine;
    }

    std::string log_level(std::string line) {

        return line.substr(1, line.find("]")-1);

    }

    std::string reformat(std::string line) {

        return message(line) + " (" + log_level(line) + ")";


    }

}





