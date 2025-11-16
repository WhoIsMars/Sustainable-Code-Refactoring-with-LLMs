#include "difference_of_squares.h"

using namespace std;

long int difference_of_squares::sum_of_squares(const int& _n) {
    int sum_of_squares {difference_of_squares::ipow(_n, 2)}, 
        n {_n};
    while (n--) sum_of_squares += difference_of_squares::ipow(n, 2);
    return sum_of_squares;
}

long int difference_of_squares::square_of_sum(const int& _n) {
    int square_of_sums {_n}, n {_n};
    while (n--) square_of_sums += n;
    return difference_of_squares::ipow(square_of_sums, 2);
}

long int difference_of_squares::difference(const int& _n) {
    return square_of_sum(_n) - sum_of_squares(_n);
}

