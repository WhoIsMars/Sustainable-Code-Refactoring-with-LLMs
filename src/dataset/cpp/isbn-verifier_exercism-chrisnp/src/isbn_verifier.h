#pragma once

#include <string>

namespace isbn_verifier {

[[nodiscard]]
auto is_valid(std::string const&) noexcept -> bool;    

} // namespace isbn_verifier


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
