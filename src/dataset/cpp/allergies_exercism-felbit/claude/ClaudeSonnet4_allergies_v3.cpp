#include "allergies.h"

namespace allergies
{

    bool allergy_test::is_allergic_to(const std::string& allergene) const
    {
        const auto it = allergenes.find(allergene);
        if (it == allergenes.end()) {
            return false;
        }
        const unsigned short alg = it->second;
        return (alg & m_score) == alg;
    }

    std::unordered_set<std::string> allergy_test::get_allergies() const
    {
        std::unordered_set<std::string> allergies;
        allergies.reserve(allergenes.size());

        for (const auto& [name, value] : allergenes)
        {
            if ((value & m_score) == value) {
                allergies.emplace(name);
            }
        }

        return allergies;
    }

} // namespace allergies