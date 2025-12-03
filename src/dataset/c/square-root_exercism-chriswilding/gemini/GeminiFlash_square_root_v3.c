#include "square_root.h"

int square_root(int n) {
    if (n < 2) {
        return n;
    }

    int low = 0;
    int high = n;
    int ans = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long square = mid * mid;

        if (square == n) {
            return mid;
        } else if (square < n) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}