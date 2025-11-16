#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>

namespace allergies {


class allergy_test {

    public:
    allergy_test(const unsigned int i);
    bool is_allergic_to(const std::string& which);
    std::unordered_set<std::string> get_allergies() const;


    private:
    void calculate_allergies();


    const unsigned int allergy_score;
    std::unordered_set<std::string> allergies;

};



}  // namespace allergies

#endif  // ALLERGIES_H