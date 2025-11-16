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

        for (const auto& allergene : allergenes)
        {
            if ((allergene.second & m_score) == allergene.second)
                allergies.emplace(allergene.first);
        }

        return allergies;
    }

} // namespace allergies