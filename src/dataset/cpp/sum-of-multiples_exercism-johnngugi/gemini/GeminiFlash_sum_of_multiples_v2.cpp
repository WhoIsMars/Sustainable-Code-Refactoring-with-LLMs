#include "sum_of_multiples.h"
#include <numeric>
#include <unordered_set>

using namespace std;

int sum_of_multiples::to(list<int> l, int n) {
    unordered_set<int> multiples;
    int sum = 0;

    for (int factor : l) {
        if (factor == 0) continue; 

        for (int multiple = factor; multiple < n; multiple += factor) {
            if (multiples.insert(multiple).second) {
                sum += multiple;
            }
        }
    }

    return sum;
}