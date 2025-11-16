#include "raindrops.h"

std::string raindrops::convert(int number) {
  std::string raindrop;
  raindrop.reserve(15); // Reserve space for "PlingPlangPlong"
  
  if (number % 3 == 0) {
    raindrop += "Pling";
  }
  if (number % 5 == 0) {
    raindrop += "Plang";
  }
  if (number % 7 == 0) {
    raindrop += "Plong";
  }
  
  return raindrop.empty() ? std::to_string(number) : raindrop;
}