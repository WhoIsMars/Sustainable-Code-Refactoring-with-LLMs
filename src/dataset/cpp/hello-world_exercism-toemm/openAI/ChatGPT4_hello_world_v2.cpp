#include "hello_world.h"
#include <string_view>

namespace hello_world {

std::string_view hello() noexcept { return "Hello, World!"; }

}  // namespace hello_world