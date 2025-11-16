#include "allergies.h"

namespace allergies
{

    bool allergy_test::is_allergic_to(const std::string& allergene) const
    {
        auto it = allergenes.find(allergene);
        if (it != allergenes.end())
        {
            return (it->second & m_score) != 0;
        }
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies() const
    {
        std::unordered_set<std::string> allergies;
        allergies.reserve(allergenes.size()); // Reserve space to avoid multiple reallocations

        for (const auto& allergene : allergenes)
        {
            if ((allergene.second & m_score) != 0)
                allergies.insert(allergene.first);
        }

        return allergies;
    }

} // namespace allergies