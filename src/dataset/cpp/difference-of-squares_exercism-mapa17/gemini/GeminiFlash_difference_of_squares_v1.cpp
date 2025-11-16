#include "difference_of_squares.h"

namespace squares {

long square_of_sums(long N) {
  if (N < 1) {
    return 0;
  }
  long sum = N * (N + 1) / 2;
  return sum * sum;
}

long sum_of_squares(long N) {
  return N * (N + 1) * (2 * N + 1) / 6;
}

long difference(long N) { return square_of_sums(N) - sum_of_squares(N); }

} // namespace squares