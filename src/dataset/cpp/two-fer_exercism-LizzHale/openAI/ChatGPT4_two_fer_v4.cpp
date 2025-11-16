#include "two_fer.h"
#include <string_view>

namespace two_fer
{

    std::string two_fer(const std::string& name) {
        constexpr std::string_view prefix = "One for ";
        constexpr std::string_view suffix = ", one for me.";
        return std::string(prefix).append(name).append(suffix);
    }

} // namespace two_fer