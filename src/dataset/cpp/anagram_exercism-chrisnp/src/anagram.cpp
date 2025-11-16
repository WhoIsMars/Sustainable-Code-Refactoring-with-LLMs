#include "anagram.h"
#include <algorithm>

using std::string;
using std::vector;

anagram::anagram::anagram(const string word) {
    this->subject = word;
    transform (this->subject.begin(), this->subject.end(),
               this->subject.begin(), ::tolower);
    this->normal = (*this).subject;
    std::sort (this->normal.begin(), this->normal.end());
}

vector<string> anagram::anagram::matches(vector<string> const &candidates) noexcept 
{
    vector<string> matching {};
    for (vector<string>::const_iterator candidate = candidates.begin();
         candidate != candidates.end(); candidate ++) 
    {
        string word = *candidate;
        transform (word.begin(), word.end(), word.begin(), ::tolower);
        string sortedLetters = word;
        sort (sortedLetters.begin(), sortedLetters.end());
        if (sortedLetters == (*this).normal && word != (*this).subject)
            matching.push_back(*candidate);
    }
    return matching;
}