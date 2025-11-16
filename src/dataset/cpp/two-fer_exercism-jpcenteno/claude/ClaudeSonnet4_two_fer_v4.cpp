#include "two_fer.h"

namespace two_fer
{

    std::string two_fer() {
        return "One for you, one for me.";
    }

    std::string two_fer(const std::string& name) {
        std::string result;
        result.reserve(13 + name.size());
        result += "One for ";
        result += name;
        result += ", one for me.";
        return result;
    }

}