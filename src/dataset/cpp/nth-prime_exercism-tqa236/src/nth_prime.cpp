#include "nth_prime.h"

#include <math.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
int nth_prime::nth(int number) {
  int count = 0;
  int upper_bound;
  if (number == 0) {
    throw domain_error("Weird case.");
  } else if (number == 1) {
    upper_bound = 2;
  } else {
    upper_bound = 10 + (int)(number * (log(number) + log(log(number))));
  }

  vector<int> numbers;
  for (int i = 1; i <= upper_bound; i++) {
    numbers.push_back(i);
  }

  for (int i = 2; i <= upper_bound; i++) {
    if (numbers[i - 1] != 0) {
      count = count + 1;
      if (count == number) {
        return numbers[i - 1];
      }
      for (int j = 2 * numbers[i - 1]; j <= upper_bound; j += numbers[i - 1]) {
        numbers[j - 1] = 0;
      }
    }
  }
  return 2;
}
