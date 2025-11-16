#pragma once

#include "test/catch.hpp"
#include <string>

namespace matching_brackets {

constexpr auto bracket = [](const char b) -> char {
    switch (b) {
        case '[': return ']';
        case '{': return '}';
        case '(': return ')';
        default : Catch::throw_domain_error("invalid bracket");
    }
};

bool check(std::string const &);

}  // namespace matching_brackets

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif