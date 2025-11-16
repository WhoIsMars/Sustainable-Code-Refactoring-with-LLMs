#include "hello_world.h"
#include <iostream>

namespace hello_world
{
  const char* hello()
  {
    return "Hello, World!";
  }

  int main() {
    std::cout << hello_world::hello() << '\n';
    return 0;
  }
}