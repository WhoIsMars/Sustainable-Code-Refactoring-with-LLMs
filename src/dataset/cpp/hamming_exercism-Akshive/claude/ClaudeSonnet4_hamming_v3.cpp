#include "hamming.h"
#include <stdexcept>
#include <string>

namespace hamming {
    int compute(std::string strand1, std::string strand2)
    {
        const std::size_t size1 = strand1.size();
        const std::size_t size2 = strand2.size();
        
        if (size1 != size2) {
            throw std::domain_error("Invalid Arguments");
        }
        
        int ans = 0;
        const char* ptr1 = strand1.data();
        const char* ptr2 = strand2.data();
        
        for (std::size_t i = 0; i < size1; ++i) {
            ans += (ptr1[i] != ptr2[i]);
        }
        
        return ans;
    }
}