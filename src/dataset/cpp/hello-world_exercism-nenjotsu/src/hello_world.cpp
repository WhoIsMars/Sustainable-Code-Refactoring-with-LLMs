#include "hello_world.h"
#include <iostream>
#include <string>

using namespace std;

namespace hello_world
{
  string hello()
  {
    return "Hello, World!";
  }

  int main() {
    cout << hello_world::hello() << endl;
    return 0;
  }
}
