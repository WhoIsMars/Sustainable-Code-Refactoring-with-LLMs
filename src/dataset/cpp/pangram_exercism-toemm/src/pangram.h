#if !defined(PANGRAM_H)
#define PANGRAM_H

#include <string>

namespace pangram {


    bool is_pangram(const std::string& sentence);
    bool is_pangram_bitset(const std::string& sentence);
    bool is_pangram_char(const std::string& sentence);
}  // namespace pangram

#endif  // PANGRAM_H