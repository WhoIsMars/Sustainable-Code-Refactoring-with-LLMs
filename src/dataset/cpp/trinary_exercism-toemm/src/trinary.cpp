#include "trinary.h"

#include <string>

namespace trinary {

    int to_decimal(const std::string& num) {

        int out{};
        int num_size = num.size();
    
        for (int i{}; i < num_size; i++) {
    
            int nr = num[num_size-1 - i] - '0';

            // catch invalid nums
            if (nr < 0 || nr > 2) return 0;

            out += nr * pow(3, i);
        }
        return out;
    }	

}  // namespace trinary
