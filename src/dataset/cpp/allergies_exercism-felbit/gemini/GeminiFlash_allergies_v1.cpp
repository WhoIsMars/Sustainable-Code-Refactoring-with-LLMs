#include "allergies.h"

#include <algorithm>

namespace allergies {

bool allergy_test::is_allergic_to(const std::string& allergene) const {
  auto it = allergenes.find(allergene);
  if (it == allergenes.end()) {
    return false; // Or throw an exception, depending on desired behavior for unknown allergens
  }
  return (it->second & m_score) == it->second;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
  std::unordered_set<std::string> allergies;
  allergies.reserve(allergenes.size()); // Pre-allocate memory

  for (const auto& [allergene, score] : allergenes) {
    if ((score & m_score) == score) {
      allergies.insert(allergene);
    }
  }

  return allergies;
}

}  // namespace allergies