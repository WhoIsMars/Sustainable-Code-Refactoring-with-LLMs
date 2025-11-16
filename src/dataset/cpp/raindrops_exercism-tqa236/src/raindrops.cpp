#include "raindrops.h"

#include <map>

std::string raindrops::convert(int number) {
  std::map<int, std::string> drops = {{3, "Pling"}, {5, "Plang"}, {7, "Plong"}};
  std::string raindrop = "";

  for (auto const& drop : drops) {
    if (number % drop.first == 0) {
      raindrop = raindrop + drop.second;
    }
  }

  if (raindrop == "") {
    return std::to_string(number);
  }
  return raindrop;
}
