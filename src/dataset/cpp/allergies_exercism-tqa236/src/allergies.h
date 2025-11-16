#pragma once
#include <string>
#include <unordered_set>

namespace allergies {
using namespace std;
class allergy_test {
 private:
  int score;
  unordered_set<string> allergies;

 public:
  allergy_test(int p_score) {
    score = p_score;
    allergies = get_allergies();
  }
  bool is_allergic_to(string);
  unordered_set<string> get_allergies();
};
}  // namespace allergies
