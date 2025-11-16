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
        for (const auto& [name, value] : allergenes)
        {
            if ((value & m_score) != 0)
                allergies.emplace(name);
        }
        return allergies;
    }

} // namespace allergies