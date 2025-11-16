#include "difference_of_squares.h"

namespace difference_of_squares {
    int square_of_sum( int limit ) {
        int result = (limit)*(limit+1)/2;
        return result*result;
    }
    int sum_of_squares( int limit ) {
        int result = 0;
        for( int i = 1; i <= limit; i++ )
            result += i*i;
        return result;
    }
    int difference( int limit ) {
        return square_of_sum(limit) - sum_of_squares(limit);
    }

}  // namespace difference_of_squares
