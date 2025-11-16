#include "etl.h"

namespace etl {


map<char, int> transform(const map<int, vector<char>>& old) {

    map<char, int> transformed;

    for(const auto& [score, letters] : old) {

        for(auto letter : letters) {

            //transform tolower
            transformed[letter+32] = score;
        }

    }
    
    return transformed;

}

}  // namespace etl
