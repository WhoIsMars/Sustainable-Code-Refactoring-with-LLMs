#pragma once

#include <string>

namespace run_length_encoding {

auto encode(const std::string&) noexcept -> std::string;
auto decode(const std::string&) noexcept -> std::string;

}  // namespace run_length_encoding


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif