#include "allergies.h"

namespace allergies
{
    bool allergy_test::is_allergic_to(std::string allergen)
    {
        std::string binaryScore = "";
        for (int score = allergy_score; score > 0; score /= 2)
            binaryScore += std::to_string(score % 2);

        if (allergen == "eggs")
            return binaryScore[0] == '1';
        if (allergen == "peanuts")
            return binaryScore[1] == '1';
        if (allergen == "shellfish")
            return binaryScore[2] == '1';
        if (allergen == "strawberries")
            return binaryScore[3] == '1';
        if (allergen == "tomatoes")
            return binaryScore[4] == '1';
        if (allergen == "chocolate")
            return binaryScore[5] == '1';
        if (allergen == "pollen")
            return binaryScore[6] == '1';
        if (allergen == "cats")
            return binaryScore[7] == '1';

        // Return false for unknown allergens
        return false;
    }

    std::unordered_set<std::string> allergy_test::get_allergies()
    {
        std::unordered_set<std::string> allergies;
        if (is_allergic_to("eggs"))
            allergies.insert("eggs");
        if (is_allergic_to("peanuts"))
            allergies.insert("peanuts");
        if (is_allergic_to("shellfish"))
            allergies.insert("shellfish");
        if (is_allergic_to("strawberries"))
            allergies.insert("strawberries");
        if (is_allergic_to("tomatoes"))
            allergies.insert("tomatoes");
        if (is_allergic_to("chocolate"))
            allergies.insert("chocolate");
        if (is_allergic_to("pollen"))
            allergies.insert("pollen");
        if (is_allergic_to("cats"))
            allergies.insert("cats");
        return allergies;
    }

    allergy_test::allergy_test(int score)
    {
        allergy_score = score;
    }
} // namespace allergies
