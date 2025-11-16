#include "two_fer.h"

namespace two_fer {

    std::string two_fer(const std::string& name) noexcept {
        static const std::string suffix = ", one for me.";
        std::string result;
        result.reserve(9 + name.size() + suffix.size());
        result = "One for ";
        result += name;
        result += suffix;
        return result;
    }

}  // namespace two_fer