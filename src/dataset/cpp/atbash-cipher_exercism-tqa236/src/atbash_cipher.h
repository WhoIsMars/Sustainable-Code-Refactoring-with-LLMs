#pragma once
#include <string>

namespace atbash_cipher {
std::string encode(const std::string &);
std::string decode(const std::string &);
std::string transform(const std::string &, bool);
}  // namespace atbash_cipher
