#include "luhn.h"

namespace luhn {



bool valid(std::string test) {

    int sum{};
    int ctr{1};

    for (auto it = test.rbegin(); it != test.rend(); it++) {

        char ch = *it;
        // only digits 

        if (isspace(ch)) continue;

        if (ch >= '0' && ch <= '9') {

            int nr = *it - '0';
            
            // every second nr.
            if (ctr % 2 == 0) {

                nr *= 2;
                if (nr > 9) nr -= 9;

            }

            sum += nr;
            ctr++;


        } else return false;

    }

    
    return !(sum % 10) && ctr > 2;



}

}  // namespace luhn
