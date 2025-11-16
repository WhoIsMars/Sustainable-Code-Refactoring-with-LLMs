#include "binary.h"

namespace binary {

int convert(std::string binary_string) {
    int sum = 0;
    int power = 1;
    
    for (int i = binary_string.size() - 1; i >= 0; --i) {
        char ch = binary_string[i];
        
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