#include "hello_world.h"
#include <iostream>

namespace hello_world
{
  std::string hello()
  {
    return "Hello, World!";
  }

  int main() {
    std::cout << hello_world::hello() << '\n';
    return 0;
  }
}