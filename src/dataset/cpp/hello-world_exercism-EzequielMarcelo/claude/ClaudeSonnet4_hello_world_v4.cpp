#include "hello_world.h"
#include <string>

namespace hello_world 
{
    std::string hello()
    {
        static const std::string result{"Hello, World!"};
        return result;
    }
}