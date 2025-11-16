#include "reverse_string.h"

namespace reverse_string {

    std::string reverse_string(const std::string& input_string) {
        if (input_string.empty()) {
            return input_string;
        }
        
        std::string result;
        result.reserve(input_string.size());
        
        for (auto it = input_string.rbegin(); it != input_string.rend(); ++it) {
            result += *it;
        }
        
        return result;
    }

}  // namespace reverse_string