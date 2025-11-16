#include "binary.h"

namespace binary {

int convert(std::string binary_string) {
    int sum = 0;
    int power = 1;
    
    for (auto it = binary_string.rbegin(); it != binary_string.rend(); ++it) {
        char ch = *it;
        
        if (ch == '1') {
            sum += power;
        } else if (ch != '0') {
            return 0;
        }
        
        power <<= 1;
    }
    
    return sum;
}

}  // namespace binary