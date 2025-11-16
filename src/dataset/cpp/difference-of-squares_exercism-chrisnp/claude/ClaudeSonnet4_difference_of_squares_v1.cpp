#include "difference_of_squares.h"

using namespace std;

long int difference_of_squares::sum_of_squares(const int& _n) {
    return static_cast<long int>(_n) * (_n + 1) * (2 * _n + 1) / 6;
}

long int difference_of_squares::square_of_sum(const int& _n) {
    long int sum = static_cast<long int>(_n) * (_n + 1) / 2;
    return sum * sum;
}

long int difference_of_squares::difference(const int& _n) {
    return square_of_sum(_n) - sum_of_squares(_n);
}