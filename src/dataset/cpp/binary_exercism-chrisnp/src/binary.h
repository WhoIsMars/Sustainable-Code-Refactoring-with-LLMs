#pragma once

#include <string>

namespace binary{

[[gnu::pure]]
auto convert(const std::string&) noexcept -> long;

}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif