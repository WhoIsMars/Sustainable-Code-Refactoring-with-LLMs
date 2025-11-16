#if !defined(ANAGRAM_H)
#define ANAGRAM_H

#include <string>
#include <unordered_set>

namespace anagram {

using namespace std;

class anagram{

    public:
    anagram(string str);

    unordered_set<string> matches(const unordered_set<string>& candidates);

    private:
    void tolower(string& str);
    string str;
};




}  // namespace anagram

#endif  // ANAGRAM_H