#if !defined(WORD_COUNT_H)
#define WORD_COUNT_H

#include <map>
#include <string>

namespace word_count {

using namespace std;

map<string, int> words(string sentence);

}  // namespace word_count

#endif  // WORD_COUNT_H