#include "nucleotide_count.h"
#include <stdexcept>
#include <unordered_map>

namespace dna {

    counter::counter(const std::string& strand) : nucleotides{{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}} {
        for (const char& nucleotide : strand) {
            auto it = nucleotides.find(nucleotide);
            if (it == nucleotides.end())
                throw std::invalid_argument(std::string("Invalid argument ") + nucleotide);
            it->second++;
        }
    }

    int counter::count(const char& c) const {
        auto it = nucleotides.find(c);
        if (it == nucleotides.end())
            throw std::invalid_argument(std::string("Invalid argument ") + c);
        return it->second;
    }

    std::unordered_map<char, int> counter::nucleotide_counts() const {
        return nucleotides;
    }

}