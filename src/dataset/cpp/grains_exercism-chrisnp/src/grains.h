#pragma once

#include <cstdint>

namespace grains {

    std::uint_least64_t square(std::uint_least16_t);
    std::uint_least64_t total();

}  // namespace grains

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif