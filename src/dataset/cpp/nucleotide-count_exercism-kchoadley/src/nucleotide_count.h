#if !defined(NUCLEOTIDE_COUNT_H)
#define NUCLEOTIDE_COUNT_H

#include <string>
#include <map>

namespace dna {
    class counter {
        private:
            std::map<char, int> nucleotides { {'A', 0}, {'T', 0}, {'C', 0}, {'G', 0} };
            std::string strand;
            
        public:
            counter(std::string strand);
            int count(const char& c) const;
            std::map<char, int> nucleotide_counts() const;
    };
}

#endif
