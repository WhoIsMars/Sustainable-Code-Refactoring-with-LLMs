#include "nucleotide_count.h"

#include <stdexcept>

namespace nucleotide_count {


std::map<char, int> count(const std::string& dna) {

    std::map<char, int> ctr{{'A', 0},
                            {'C', 0},
                            {'G', 0},
                            {'T', 0}};

    for (auto nuc: dna) {

        auto ctr_nuc = ctr.find(nuc);
        if (ctr_nuc != ctr.end()) {
            ctr_nuc->second += 1;
        } else {
            throw std::invalid_argument("invalid nuc");
        }

    }
    return ctr;
}

}  // namespace nucleotide_count
