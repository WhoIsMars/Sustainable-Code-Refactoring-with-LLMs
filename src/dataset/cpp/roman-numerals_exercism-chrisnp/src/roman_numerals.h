#pragma once

#include <string>

namespace roman_numerals {

struct numeral_mapping {
    unsigned int arabic;
    char const* roman;
};

static const numeral_mapping arabic_to_roman[] {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
    {90, "XC"},  {50, "L"},   {40, "XL"},  {10, "X"},
    {9, "IX"},   {5, "V"},    {4, "IV"},  {1, "I"}
};

std::string convert(unsigned int number);

}  // namespace roman_numerals

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif