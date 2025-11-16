#include "pangram.h"

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>

namespace pangram {

    bool is_pangram_string(const std::string& sentence) {
        bool found[26] = {false};
        int count = 0;
        
        for (char c : sentence) {
            if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (!found[index]) {
                    found[index] = true;
                    if (++count == 26) return true;
                }
            } else if (c >= 'A' && c <= 'Z') {
                int index = c - 'A';
                if (!found[index]) {
                    found[index] = true;
                    if (++count == 26) return true;
                }
            }
        }
        
        return count == 26;
    }

    bool is_pangram_char(const std::string& sentence) {
        bool found[26] = {false};
        int count = 0;
        
        for (char c : sentence) {
            if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (!found[index]) {
                    found[index] = true;
                    if (++count == 26) return true;
                }
            } else if (c >= 'A' && c <= 'Z') {
                int index = c - 'A';
                if (!found[index]) {
                    found[index] = true;
                    if (++count == 26) return true;
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
            
            if (alphabet_set.count() == 26) return true;
        }

        return alphabet_set.count() == 26;
    }

    bool is_pangram(const std::string& sentence) {
        bool found[26] = {false};
        int count = 0;
        
        for (char c : sentence) {
            if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (!found[index]) {
                    found[index] = true;
                    if (++count == 26) return true;
                }
            } else if (c >= 'A' && c <= 'Z') {
                int index = c - 'A';
                if (!found[index]) {
                    found[index] = true;
                    if (++count == 26) return true;
                }
            }
        }
        
        return count == 26;
    }
}