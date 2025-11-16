#include "sum_of_multiples.h"

#include <iostream>
#include <random>
#include <vector>
using namespace std;

int sum_of_multiples::to(vector<int> factors, int limit) {
  vector<int> numbers;
  for (int i = 1; i < limit; i++) {
    for (auto p : factors) {
      if (i % p == 0) {
        numbers.push_back(i);
        break;
      }
    }
  }
  int sum = 0;
  for (auto& n : numbers) {
    sum += n;
  }
  return sum;
}
