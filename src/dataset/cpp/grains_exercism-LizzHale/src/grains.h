#if !defined(GRAINS_H)
#define GRAINS_H

#include <cstdint>

namespace grains {

    const int max_squares = 64;
    std::uint64_t square(int number);
    std::uint64_t total();

}  // namespace grains

#endif // GRAINS_H