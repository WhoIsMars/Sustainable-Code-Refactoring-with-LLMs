#include "reverse_string.h"
#include <algorithm>
#include <string>

namespace reverse_string {

    std::string reverse_string(const std::string& sentence) {
        std::string reversed(sentence.rbegin(), sentence.rend());
        return reversed;
    }

}