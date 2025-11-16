#include "hello_world.h"
#include <string_view>

namespace hello_world {
    std::string_view hello() noexcept {
        static constexpr std::string_view message = "Hello, World!";
        return message;
    }
}