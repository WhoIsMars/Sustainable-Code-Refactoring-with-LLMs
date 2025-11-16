#include "two_fer.h"

namespace two_fer
{

    std::string two_fer() {
        return "One for you, one for me.";
    }

    std::string two_fer(const std::string& name) {
        std::string result;
        result.reserve(9 + name.size() + 15);
        result = "One for ";
        result += name;
        result += ", one for me.";
        return result;
    }

} // namespace two_fer