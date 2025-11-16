#pragma once
#include <vector>
#include <string>
#include <unordered_set>

namespace allergies {

using ushort = unsigned short;
typedef std::unordered_set<std::string> allergies_t;
typedef std::vector<std::string> allergens_t;

class allergy_test {
public:
    [[nodiscard]]
    explicit allergy_test(ushort);
    auto is_allergic_to(const std::string&) noexcept -> bool;
    [[nodiscard]]
    auto get_allergies() const -> allergies_t;
private:
    ushort score;
    allergies_t allergies;
    allergens_t ALLERGENS = {
        "eggs", "peanuts", "shellfish", "strawberries",
        "tomatoes", "chocolate", "pollen", "cats"
    };
};

}  // namespace allergies

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif