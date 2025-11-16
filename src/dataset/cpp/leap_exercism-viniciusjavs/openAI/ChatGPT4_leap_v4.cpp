#include "leap.h"

namespace leap {
inline bool is_leap_year(int year) noexcept {
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}
} // namespace leap