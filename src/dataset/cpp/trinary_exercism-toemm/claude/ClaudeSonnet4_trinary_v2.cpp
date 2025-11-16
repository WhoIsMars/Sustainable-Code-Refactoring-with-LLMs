#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {
        int out{};
        int power_of_3 = 1;
        
        for (int i = num.size() - 1; i >= 0; --i) {
            int nr = num[i] - '0';
            
            // catch invalid nums
            if (nr < 0 || nr > 2) return 0;
            
            out += nr * power_of_3;
            power_of_3 *= 3;
        }
        return out;
    }

}  // namespace trinary