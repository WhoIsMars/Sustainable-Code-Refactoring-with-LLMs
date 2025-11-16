#include "reverse_string.h"

namespace reverse_string {

    std::string reverse_string(const std::string& input_string) {
        std::string reversed = input_string;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

}  // namespace reverse_string