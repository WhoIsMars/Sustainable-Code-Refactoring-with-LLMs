#include <string>
#include <unordered_map>
#include <iostream>
#include "word_count.h"
using namespace std;

map<string, int> word_count::words(string sen)
{
    string store;
    store.reserve(32); // Reserve space to avoid frequent reallocations
    unordered_map<string, int> word_counts;
    
    auto process_word = [&]() {
        if (!store.empty()) {
            if (store.back() == '\'') {
                store.pop_back();
            }
            ++word_counts[store];
            store.clear();
        }
    };

    for (char c : sen) {
        if (isalnum(c)) {
            store += static_cast<char>(tolower(c));
        } else if (c == '\'' && !store.empty()) {
            store += c;
        } else {
            process_word();
        }
    }
    
    process_word(); // Handle the last word
    
    // Convert to map to maintain original return type
    return map<string, int>(word_counts.begin(), word_counts.end());
}