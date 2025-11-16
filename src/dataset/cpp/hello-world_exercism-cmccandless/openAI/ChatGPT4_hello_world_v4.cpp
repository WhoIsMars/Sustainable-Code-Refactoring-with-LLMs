#include "hello_world.h"

const std::string& hello_world::hello() {
    static const std::string message = "Hello, World!";
    return message;
}