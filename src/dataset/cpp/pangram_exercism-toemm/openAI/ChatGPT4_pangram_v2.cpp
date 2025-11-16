#include "pangram.h"

#include <bitset>
#include <string>
#include <cctype>

namespace pangram {

    bool is_pangram_string(const std::string& sentence) {
        std::bitset<26> alphabet_set;

        for (char c : sentence) {
            if (std::isalpha(c)) {
                alphabet_set.set(std::tolower(c) - 'a');
                if (alphabet_set.all()) return true;
            }
        }

        return alphabet_set.all();
    }

    bool is_pangram_char(const std::string& sentence) {
        std::bitset<26> alphabet_set;

        for (char c : sentence) {
            if (std::isalpha(c)) {
                alphabet_set.set(std::tolower(c) - 'a');
                if (alphabet_set.all()) return true;
            }
        }

        return alphabet_set.all();
    }

    bool is_pangram_bitset(const std::string& sentence) {
        std::bitset<26> alphabet_set;

        for (char c : sentence) {
            if (std::isalpha(c)) {
                alphabet_set.set(std::tolower(c) - 'a');
                if (alphabet_set.all()) return true;
            }
        }

        return alphabet_set.all();
    }

    bool is_pangram(const std::string& sentence) {
        return is_pangram_bitset(sentence);
    }
}