#pragma once

namespace perfect_numbers {

enum classification {
    abundant,
    perfect,
    deficient
};

auto classify(int) -> classification;

}  // namespace perfect_numbers

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif