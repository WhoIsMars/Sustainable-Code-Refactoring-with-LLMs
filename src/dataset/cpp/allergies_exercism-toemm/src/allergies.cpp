#include "allergies.h"

namespace allergies {


static const std::vector<std::string> allergens{
                                                "eggs", "peanuts", "shellfish", 
                                                "strawberries", "tomatoes", "chocolate",
                                                "pollen", "cats"};

allergy_test::allergy_test(const unsigned int i): allergy_score(i), allergies({}) {
    calculate_allergies();
}

bool allergy_test::is_allergic_to(const std::string& which) {
    
    return allergies.find(which) != allergies.end();

}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    return allergies;
}

void allergy_test::calculate_allergies() {

    for (std::size_t i{}; i < allergens.size(); i++) {

        if (allergy_score & (1 << i)) allergies.insert(allergens[i]);
    }
}


}  // namespace allergies
