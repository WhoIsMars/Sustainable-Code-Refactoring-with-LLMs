#include "grade_school.h"
#include <algorithm>

namespace grade_school {
roster_t const &school::roster() const { return roster_; }

void school::add(string name, int grade) {
  auto &students = roster_[grade];
  students.insert(std::upper_bound(students.begin(), students.end(), name), std::move(name));
}

vector<string> school::grade(int grade) const {
  auto it = roster_.find(grade);
  return it != roster_.end() ? it->second : vector<string>{};
}
} // namespace grade_school