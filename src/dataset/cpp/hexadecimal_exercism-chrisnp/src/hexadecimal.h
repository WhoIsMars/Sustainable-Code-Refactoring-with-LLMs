#pragma once

#include <string>
#include <cstdint>

using namespace std;

namespace hexadecimal {

auto convert(const string&) noexcept -> uint64_t;

}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif