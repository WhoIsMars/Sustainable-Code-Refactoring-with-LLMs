#include "gigasecond.h"

#include <chrono>

namespace gigasecond {

ptime advance(ptime time) {
  static const long long gigasecond = 1000000000LL;
  time += seconds(gigasecond);
  return time;
}

}  // namespace gigasecond