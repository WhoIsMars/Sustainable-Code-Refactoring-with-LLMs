#include "gigasecond.h"
#include <chrono>

namespace gigasecond {
ptime advance(const ptime &time) {
  static const std::chrono::seconds gigasecond_duration(1000000000);
  auto time_point = time_facet::ptime_to_chrono(time);
  auto advanced_time_point = time_point + gigasecond_duration;
  return time_facet::chrono_to_ptime(advanced_time_point);
}
}  // namespace gigasecond