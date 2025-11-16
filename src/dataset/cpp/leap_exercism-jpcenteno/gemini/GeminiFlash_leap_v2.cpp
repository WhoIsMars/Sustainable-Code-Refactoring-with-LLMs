#include "leap.h"

namespace leap {

bool is_leap_year(const int year) {
  if (year % 4 != 0) {
    return false;
  }
  if (year % 100 == 0) {
    return (year % 400 == 0);
  }
  return true;
}

}  // namespace leap