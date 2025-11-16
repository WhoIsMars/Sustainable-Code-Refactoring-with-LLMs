#include "hello_world.h"
#include <iostream>

namespace hello_world
{
  constexpr const char* hello()
  {
    return "Hello, World!";
  }

  int main() {
    std::cout << hello() << '\n';
    return 0;
  }
}