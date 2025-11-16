#include "hello_world.h"

using namespace std;

namespace hello_world {

string hello() { 
    static const string result = "Hello, World!";
    return result;
}

}  // namespace hello_world