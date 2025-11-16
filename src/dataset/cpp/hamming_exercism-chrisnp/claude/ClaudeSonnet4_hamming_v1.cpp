#include "hamming.h"

using namespace std;

namespace hamming {

int compute(const string& strand1, const string& strand2) {

    if (strand1.size() != strand2.size())
        throw domain_error("Strands are not of same length");

    int count = 0;
    const size_t size = strand1.size();
    
    for (size_t i = 0; i < size; ++i) {
        if (strand1[i] != strand2[i]) {
            ++count;
        }
    }
    
    return count;
} // compute

}  // namespace hamming