#include "difference_of_squares.h"

namespace difference_of_squares {

int square_of_sum(int limit) {
    int sum = 0;
    
    for (int i = 1; i <= limit; ++i)
        sum += i;
    
    return sum * sum;
}

int sum_of_squares(int limit) {
    int sum = 0;
    
    for (int i = 1; i <= limit; ++i)
        sum += i * i;
    
    return sum;
}

int difference(int limit) {
    return square_of_sum(limit) - sum_of_squares(limit);
}

}  // namespace difference_of_squares
