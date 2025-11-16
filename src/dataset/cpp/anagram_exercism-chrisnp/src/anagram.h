#pragma once

#include <string>
#include <vector>

namespace anagram {
    using std::string;
    using std::vector;

class anagram {
public:
    [[nodiscard]]
    explicit anagram(string const);
    auto matches(vector<string> const &) noexcept -> vector<string>;
private:
    string subject;
    string normal;
};
}  // namespace anagram

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif