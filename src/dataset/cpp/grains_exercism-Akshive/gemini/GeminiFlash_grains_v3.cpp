#include "grains.h"

namespace grains {

unsigned long long square(int sq) {
  if (sq < 1 || sq > 64) {
    return 0;
  }
  return (1ULL << (sq - 1));
}

unsigned long long total() {
  return ~0ULL;
}

} // namespace grains