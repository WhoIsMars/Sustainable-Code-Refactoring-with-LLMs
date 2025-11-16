#include "hello_world.h"
#include <string>

std::string hello_world::hello() noexcept {
    static const std::string message = "Hello, World!";
    return message;
}