#include <array>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <string_view>

#include "allergies.h"

namespace {
    static constexpr std::array<std::pair<std::string_view, unsigned short>, 8> _allergy_list
    {{
        {"eggs", 1}, {"peanuts", 2}, {"shellfish", 4}, {"strawberries", 8},
        {"tomatoes", 16}, {"chocolate", 32}, {"pollen", 64}, {"cats", 128}
    }};
    
    static const std::unordered_map<std::string_view, unsigned short> _allergy_map = []() {
        std::unordered_map<std::string_view, unsigned short> map;
        for (const auto& allergy : _allergy_list) {
            map.emplace(allergy.first, allergy.second);
        }
        return map;
    }();
}

allergies::allergy_test::allergy_test(unsigned short n) : _allergie_score{n} {}

bool allergies::allergy_test::is_allergic_to(std::string const& aller) const {
    auto it = _allergy_map.find(aller);
    return it != _allergy_map.end() && (_allergie_score & it->second) != 0;
}

std::unordered_set<std::string> allergies::allergy_test::get_allergies() const {
    std::unordered_set<std::string> _all_list;
    _all_list.reserve(8);
    
    for (const auto& ele : _allergy_list) {
        if ((_allergie_score & ele.second) != 0) {
            _all_list.emplace(ele.first);
        }
    }
    return _all_list;
}