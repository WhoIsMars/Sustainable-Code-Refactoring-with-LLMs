#include "two_fer.h"

namespace two_fer {

    std::string two_fer(const std::string& name) {
        std::string result;
        result.reserve(18 + name.size()); // Pre-allocate memory
        result = "One for ";
        result += name;
        result += ", one for me.";
        return result;
    }

}  // namespace two_fer