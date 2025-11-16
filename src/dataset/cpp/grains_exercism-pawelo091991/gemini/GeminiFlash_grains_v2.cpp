#include "grains.h"
#include <stdexcept>

unsigned long long grains::square(unsigned int field) {
  if (field == 0 || field > 64) {
    throw std::domain_error("Field must be between 1 and 64");
  }
  return (1ULL << (field - 1));
}

unsigned long long grains::total() {
  return ~0ULL;
}