#include <stdexcept>
#include <string>

namespace hamming {
int compute(const std::string& dna1, const std::string& dna2) {
    if (dna1.size() != dna2.size()) {
        throw std::domain_error("2 DNAs have different lengths.");
    }
    int hamming_distance = 0;
    for (size_t i = 0, n = dna1.size(); i < n; ++i) {
        hamming_distance += (dna1[i] != dna2[i]);
    }
    return hamming_distance;
}
}  // namespace hamming