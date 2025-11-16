#include <array>
#include <utility>
#include <unordered_map>

#include "allergies.h"

namespace{
static const std::array<std::pair<std::string_view, unsigned short>, 8> _allergy_list
{{ {"eggs", 1}, {"peanuts", 2}, {"shellfish", 4}, {"strawberries", 8}, {"tomatoes", 16}, {"chocolate", 32}, {"pollen", 64}, {"cats", 128} }};

static const std::unordered_map<std::string_view, unsigned short> _allergy_map
{{ {"eggs", 1}, {"peanuts", 2}, {"shellfish", 4}, {"strawberries", 8}, {"tomatoes", 16}, {"chocolate", 32}, {"pollen", 64}, {"cats", 128} }};
}

// Constructor for allergy_test
allergies::allergy_test::allergy_test(unsigned short n) : _allergie_score{static_cast<unsigned char>(n & 0xFF)} {}

bool allergies::allergy_test::is_allergic_to(std::string const& aller) const
{
    auto it = _allergy_map.find(aller);
    return it != _allergy_map.end() && (_allergie_score & it->second) != 0;
}

std::unordered_set<std::string> allergies::allergy_test::get_allergies() const
{
    std::unordered_set<std::string> _all_list;
    _all_list.reserve(8);
    
    for(const auto& ele : _allergy_list)
    {
        if((_allergie_score & ele.second) != 0) 
            _all_list.emplace(ele.first);
    }
    return _all_list;
}