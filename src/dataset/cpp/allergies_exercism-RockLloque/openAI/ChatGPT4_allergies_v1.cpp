#include <array>
#include <unordered_set>
#include <string>

#include "allergies.h"

namespace {
constexpr std::array<std::pair<std::string_view, unsigned short>, 8> _allergy_list{{
    {"eggs", 1 << 0}, {"peanuts", 1 << 1}, {"shellfish", 1 << 2}, {"strawberries", 1 << 3},
    {"tomatoes", 1 << 4}, {"chocolate", 1 << 5}, {"pollen", 1 << 6}, {"cats", 1 << 7}
}};
}

// Constructor for allergy_test
allergies::allergy_test::allergy_test(unsigned short n) : _allergie_score{n} {}

bool allergies::allergy_test::is_allergic_to(std::string const& aller) const {
    for (const auto& ele : _allergy_list) {
        if (ele.first == aller) return (ele.second & _allergie_score) != 0;
    }
    return false;
}

std::unordered_set<std::string> allergies::allergy_test::get_allergies() const {
    std::unordered_set<std::string> _all_list;
    for (const auto& ele : _allergy_list) {
        if ((ele.second & _allergie_score) != 0) {
            _all_list.emplace(ele.first);
        }
    }
    return _all_list;
}