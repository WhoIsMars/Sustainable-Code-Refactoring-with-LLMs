#include "hello_world.h"

// Define the function as a static constant to avoid re-evaluation.
static const char *message = "Hello, World!";
const char *hello(void) { return message; }