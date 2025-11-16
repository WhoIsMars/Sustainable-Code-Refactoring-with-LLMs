#include "hamming.h"

using namespace std;

namespace hamming {

int compute(const string strand1, const string strand2) {

    if (strand1.size() != strand2.size())
        throw domain_error("Strands are not of same length");

    return inner_product(strand1.begin(), strand1.end(), 
                         strand2.begin(),
                         0,
                         plus<int>(),
                         not_equal_to<char>());
} // compute

}  // namespace hamming
