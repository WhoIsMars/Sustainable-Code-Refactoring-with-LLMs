#include "grains.h"


namespace grains {



    unsigned long long square(int squares) {

        /*
        squares = 0

        0000 .... 0001 = 1 * 2^0 = 1

        squares = 1

        0000 .... 0010 = 0 * 2^0 + 1 * 2^1 = 2

        squares = 2

        0000 .... 0100 = 0 * 2^0 + 0 * 2^0 + 1 * 2^2 = 4
        
        
        */
        return 1ULL << (squares-1);
    }

    unsigned long long total() {

        int i{1};
        unsigned long long squares_total{};
        while (i <= 64) {
            squares_total += square(i);
            i++;
        }

        return squares_total;
    }

    

}  // namespace grains
