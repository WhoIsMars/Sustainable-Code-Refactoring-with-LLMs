#include "pangram.h"

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>

namespace pangram {


    bool is_pangram_string(const std::string& sentence) {
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

        for (std::size_t i{}; i < sentence.length(); i++) {

            char char_string = std::tolower(sentence[i]);

            for (std::size_t j{}; j < alphabet.length(); j++) {

                if (char_string == alphabet[j]) {

                    //std::cout << char_string << alphabet[j] << std::endl;
                    alphabet.erase(j, 1);

                }
            }

        }

        //std::cout << alphabet << alphabet.size() << std::endl;
        return !alphabet.size();
    }

    bool is_pangram_char(const std::string& sentence) {

        const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
        const char* end = alphabet + strlen(alphabet);

        char cp_alphabet[26] = {};
        int cp_alphabet_index = 0;
        
        //std::cout << std::strlen(alphabet) << std::endl;

        const char* sentence_ptr = sentence.c_str();

        while (*sentence_ptr) {

            char c = tolower(*sentence_ptr);
            //std::cout << "iterating through sentence: " << *sentence_ptr << std::endl;
            for (const char* beg = alphabet; beg < end; beg++) {

                //std::cout << "iterating through alphabet: " << *beg << std::endl;

                if (c == *beg) {
                    bool found = false;
                    
                    //std::cout << "match found." << std::endl;

                    for (int index = 0; index < cp_alphabet_index; index++) {
                        if (cp_alphabet[index] == c) {
                            found = true;
                            //std::cout << c << " already found, skipping" << std::endl;
                            break;
                        }
                    }

                    if (!found) {
                        //std::cout << "not yet found: " << *sentence_ptr << std::endl;
                        cp_alphabet[cp_alphabet_index++] = c;
                        //printf("%s\n", cp_alphabet);

                    }


                }
                
            }

            sentence_ptr++;

        }
        //std::cout << strlen(cp_alphabet) << std::endl;
        //printf("%s \n", cp_alphabet);

        cp_alphabet[cp_alphabet_index] = '\0';
        //printf("%s\n", cp_alphabet);
        //std::cout << strlen(cp_alphabet) << std::endl;
        return cp_alphabet_index == 26;

    }

 

    bool is_pangram_bitset(const std::string& sentence) {
        std::bitset<26> alphabet_set;

        for (char c : sentence) {
            //std::cout << c << std::endl;
    
            if (isalpha(c)) {
             
                alphabet_set.set(tolower(c) - 'a');
    
            }
        }
    
    
        return alphabet_set.count() == 26;
    }

    
    bool is_pangram(const std::string& sentence) {


        //is_pangram_char(sentence);
        return is_pangram_bitset(sentence);


        
    }
} 

