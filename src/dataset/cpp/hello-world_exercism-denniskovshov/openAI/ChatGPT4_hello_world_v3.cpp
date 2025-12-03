#include "hello_world.h"

namespace hello_world {

inline std::string hello() noexcept {
    static const std::string message = "Hello, World!";
    return message;
}

}  // namespace hello_world