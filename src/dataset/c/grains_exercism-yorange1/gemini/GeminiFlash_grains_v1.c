#include "grains.h"
#include <math.h>

uint64_t square(uint8_t index) {
  if (index == 0 || index > 64) {
    return 0;
  }
  return (uint64_t)pow(2, index - 1);
}

uint64_t total(void) { return (uint64_t)pow(2, 64) - 1; }