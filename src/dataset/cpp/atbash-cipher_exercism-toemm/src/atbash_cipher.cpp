#include "atbash_cipher.h"


namespace atbash_cipher {

std::string encode(const std::string& msg) {
    std::string out;

    int ctr{0};

    for (auto ch : msg) {

        if (isalpha(ch)) {
            char lower_ch = tolower(ch);
                if (ctr % 5 == 0 && ctr > 0) out += " ";

                out += 97 + 122 - lower_ch;
                ctr++;
            }
        
        else if (isdigit(ch)) {
            if (ctr % 5 == 0 && ctr > 0) out += " ";

            ctr++;
            out += ch;
        } 
    }


    return out;
}


std::string decode(const std::string& msg) {


    std::string out;

    // remove whitespaces
    for (auto ch : msg) {
        if (isalpha(ch)) {
            out += 97 + (122 - tolower(ch));
        }
        if (isdigit(ch)) {
            out += ch;
        }
    }
    return out;
}


}  // namespace atbash_cipher
