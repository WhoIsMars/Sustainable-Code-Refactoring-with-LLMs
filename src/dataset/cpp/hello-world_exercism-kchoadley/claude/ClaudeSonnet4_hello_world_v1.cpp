#include "hello_world.h"

#include <string_view>

namespace hello_world {
    std::string hello()
    {
        static constexpr std::string_view hello_msg = "Hello, World!";
        return std::string{hello_msg};
    }
}