#include "hello_world.h"

std::string hello_world::hello() noexcept { 
    static const std::string result{"Hello, World!"};
    return result;
}