#include "reverse_string.h"
#include <algorithm>

namespace reverse_string {

    std::string reverse_string(const std::string& input_string) {
        std::string reversed_string(input_string);
        std::reverse(reversed_string.begin(), reversed_string.end());
        return reversed_string;
    }

}  // namespace reverse_string