#if !defined(PANGRAM_H)
#define PANGRAM_H

#include <string>

namespace pangram {

    bool is_pangram(std::string sentence);
    bool is_in_sentence(char character, std::string sentence);

}  // namespace pangram

#endif // PANGRAM_H