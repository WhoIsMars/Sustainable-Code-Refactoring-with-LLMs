#pragma once

#include <array>
#include <random>
#include <string>
#include <string_view>
#include <map>
#include <unordered_map>

namespace parallel_letter_frequency {

    std::unordered_map<char, int> frequency(std::vector<std::string_view> texts);






}
