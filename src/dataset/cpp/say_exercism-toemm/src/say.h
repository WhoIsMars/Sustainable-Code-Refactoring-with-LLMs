#if !defined(SAY_H)
#define SAY_H

#include <string>
#include <vector>

namespace say {

std::string in_english(long long i);
std::string in_english_100(int i);
std::vector<int> break_up(long long i);
}  // namespace say

#endif  // SAY_H