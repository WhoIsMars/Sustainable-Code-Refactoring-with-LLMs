#include "hello_world.h"

std::string hello_world::hello() noexcept {
    static const std::string message = "Hello, World!";
    return message;
}