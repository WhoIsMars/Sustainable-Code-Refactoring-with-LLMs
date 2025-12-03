#include "hello_world.h"
#include <string>

namespace hello_world{
	const std::string hello_message = "Hello, World!";
	std::string hello(){
		return hello_message;
	}
}