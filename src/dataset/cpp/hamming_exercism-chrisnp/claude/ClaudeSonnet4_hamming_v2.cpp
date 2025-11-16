#include "hamming.h"

using namespace std;

namespace hamming {

int compute(const string& strand1, const string& strand2) {
    const size_t size = strand1.size();
    
    if (size != strand2.size())
        throw domain_error("Strands are not of same length");

    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        count += (strand1[i] != strand2[i]);
    }
    
    return count;
} // compute

}  // namespace hamming