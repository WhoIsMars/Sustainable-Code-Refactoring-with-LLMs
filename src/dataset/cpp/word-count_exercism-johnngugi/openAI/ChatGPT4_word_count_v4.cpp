#include <string>
#include <map>
#include <cctype>
#include <unordered_map>
#include "word_count.h"
using namespace std;

map<string, int> word_count::words(const string& sen)
{
    unordered_map<string, int> word_freq;
    string store;

    for (char c : sen)
    {
        if (isalnum(c))
        {
            store += tolower(c);
        }
        else if (c == '\'' && !store.empty())
        {
            store += c;
        }
        else if (!store.empty())
        {
            if (store.back() == '\'')
            {
                store.pop_back();
            }
            ++word_freq[store];
            store.clear();
        }
    }

    if (!store.empty())
    {
        if (store.back() == '\'')
        {
            store.pop_back();
        }
        ++word_freq[store];
    }

    return map<string, int>(word_freq.begin(), word_freq.end());
}