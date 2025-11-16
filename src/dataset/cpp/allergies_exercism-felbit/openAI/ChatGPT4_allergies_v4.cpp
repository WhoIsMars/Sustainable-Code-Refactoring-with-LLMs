#include "allergies.h"

namespace allergies
{

    bool allergy_test::is_allergic_to(const std::string& allergene) const
    {
        auto it = allergenes.find(allergene);
        return it != allergenes.end() && (it->second & m_score) == it->second;
    }

    std::unordered_set<std::string> allergy_test::get_allergies() const
    {
        std::unordered_set<std::string> allergies;
        allergies.reserve(allergenes.size());

        for (const auto& [name, value] : allergenes)
        {
            if ((value & m_score) == value)
                allergies.insert(name);
        }

        return allergies;
    }

} // namespace allergies