#include "isogram.h"

#include <string>

namespace isogram {

bool is_isogram(const std::string& str) {

    std::string abc;

    for (char ch : str) {

        ch = tolower(ch);
        if (isalpha(ch) && abc.find(ch) != std::string::npos) return false;
        if (isalpha(ch) && abc.find(ch) == std::string::npos) abc.push_back(ch);
    }


    return true;

}

}  // namespace isogram
