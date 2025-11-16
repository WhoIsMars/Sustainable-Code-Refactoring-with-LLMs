#include "pangram.h"

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>

namespace pangram {

    bool is_pangram_string(const std::string& sentence) {
        std::bitset<26> seen;
        
        for (char c : sentence) {
            if (c >= 'a' && c <= 'z') {
                seen.set(c - 'a');
            } else if (c >= 'A' && c <= 'Z') {
                seen.set(c - 'A');
            }
            
            if (seen.count() == 26) {
                return true;
            }
        }
        
        return seen.count() == 26;
    }

    bool is_pangram_char(const std::string& sentence) {
        bool seen[26] = {false};
        int count = 0;
        
        for (char c : sentence) {
            int index = -1;
            if (c >= 'a' && c <= 'z') {
                index = c - 'a';
            } else if (c >= 'A' && c <= 'Z') {
                index = c - 'A';
            }
            
            if (index >= 0 && !seen[index]) {
                seen[index] = true;
                count++;
                if (count == 26) {
                    return true;
                }
            }
        }
        
        return count == 26;
    }

    bool is_pangram_bitset(const std::string& sentence) {
        std::bitset<26> alphabet_set;

        for (char c : sentence) {
            if (c >= 'a' && c <= 'z') {
                alphabet_set.set(c - 'a');
            } else if (c >= 'A' && c <= 'Z') {
                alphabet_set.set(c - 'A');
            }
            
            if (alphabet_set.count() == 26) {
                return true;
            }
        }

        return alphabet_set.count() == 26;
    }

    bool is_pangram(const std::string& sentence) {
        return is_pangram_char(sentence);
    }
}