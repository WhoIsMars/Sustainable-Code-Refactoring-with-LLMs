#include "hamming.h"

using namespace std;

namespace hamming {

int compute(const string strand1, const string strand2) {
    const size_t size1 = strand1.size();
    const size_t size2 = strand2.size();
    
    if (size1 != size2)
        throw domain_error("Strands are not of same length");

    int count = 0;
    const char* ptr1 = strand1.data();
    const char* ptr2 = strand2.data();
    
    for (size_t i = 0; i < size1; ++i) {
        count += (ptr1[i] != ptr2[i]);
    }
    
    return count;
}

}  // namespace hamming