#include "hello_world.h"
#include <iostream>
#include <string>

namespace hello_world
{
  std::string hello() noexcept
  {
    return "Hello, World!";
  }

  int main() noexcept {
    static const auto message = hello();
    std::cout << message << '\n';
    return 0;
  }
}