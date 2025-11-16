#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace anagram {
class anagram {
 private:
  std::string lower_word;
  std::string normalized_word;
  std::tuple<std::string, std::string> process_word(std::string word);

 public:
  explicit anagram(std::string const& word);
  std::vector<std::string> matches(std::vector<std::string> const& candidates);
};
}  // namespace anagram
