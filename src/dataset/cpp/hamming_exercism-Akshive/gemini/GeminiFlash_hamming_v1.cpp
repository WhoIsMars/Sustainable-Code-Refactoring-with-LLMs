#include "hamming.h"
#include <string>
#include <stdexcept>

namespace hamming {
    int compute(const std::string& strand1, const std::string& strand2) {
        if (strand1.size() != strand2.size()) {
            throw std::domain_error("Strands must be of equal length.");
        }

        int distance = 0;
        for (size_t i = 0; i < strand1.size(); ++i) {
            if (strand1[i] != strand2[i]) {
                ++distance;
            }
        }
        return distance;
    }
}