#include "difference_of_squares.h"

namespace difference_of_squares {


int square_of_sum(int i) {
    int sum{};
    for (int j = 1; j <= i; j++) {
        sum += j;
    }

    return sum*sum;
}

int sum_of_squares(int i) {

    int sum{};
    for (int j = 1; j <= i; j++) {
        sum += j*j;
    }

    return sum;
}

int difference(int i) {
    return square_of_sum(i) - sum_of_squares(i);
}


}  // namespace difference_of_squares  test
