#include <array>
#include <utility>
#include <unordered_set>
#include <string_view>

#include "allergies.h"

namespace {
    static constexpr std::array<std::pair<std::string_view, unsigned short>, 8> _allergy_list
    {{{"eggs", 1}, {"peanuts", 2}, {"shellfish", 4}, {"strawberries", 8}, 
      {"tomatoes", 16}, {"chocolate", 32}, {"pollen", 64}, {"cats", 128}}};
}

allergies::allergy_test::allergy_test(unsigned short n) : _allergie_score{n} {}

bool allergies::allergy_test::is_allergic_to(std::string const& aller) const
{
    for (const auto& ele : _allergy_list) {
        if (ele.first == aller) {
            return (ele.second & _allergie_score) != 0;
        }
    }
    return false;
}

std::unordered_set<std::string> allergies::allergy_test::get_allergies() const
{
    std::unordered_set<std::string> _all_list;
    _all_list.reserve(8);
    
    for (const auto& ele : _allergy_list) {
        if ((ele.second & _allergie_score) != 0) {
            _all_list.emplace(ele.first);
        }
    }
    return _all_list;
}