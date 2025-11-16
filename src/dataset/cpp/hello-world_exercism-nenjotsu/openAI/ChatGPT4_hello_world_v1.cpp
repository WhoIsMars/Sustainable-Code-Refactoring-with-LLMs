#include "hello_world.h"
#include <iostream>

namespace hello_world
{
  inline const std::string& hello()
  {
    static const std::string message = "Hello, World!";
    return message;
  }

  int main() {
    std::cout << hello() << '\n';
    return 0;
  }
}