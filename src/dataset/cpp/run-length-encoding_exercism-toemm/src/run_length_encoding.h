#pragma once

#include <string>

namespace run_length_encoding {

std::string encode(const std::string& in) noexcept;

std::string decode(const std::string& in) noexcept;

}  // namespace run_length_encoding
