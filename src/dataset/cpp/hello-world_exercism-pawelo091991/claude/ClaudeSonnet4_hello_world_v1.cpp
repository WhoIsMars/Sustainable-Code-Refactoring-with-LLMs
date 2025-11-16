#include "hello_world.h"
#include <string_view>

namespace hello_world{
	std::string_view hello(){
		static constexpr std::string_view result = "Hello, World!";
		return result;
	}
}