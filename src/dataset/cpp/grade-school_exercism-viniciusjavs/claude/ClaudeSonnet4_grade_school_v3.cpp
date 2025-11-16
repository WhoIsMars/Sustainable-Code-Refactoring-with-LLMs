#include "grade_school.h"
#include <algorithm>

namespace grade_school {
roster_t const &school::roster() const { return roster_; }

void school::add(string name, int grade) {
  auto &students = roster_[grade];
  if (students.empty()) {
    students.push_back(std::move(name));
  } else {
    auto pos = std::lower_bound(students.begin(), students.end(), name);
    if (pos == students.end() || *pos != name) {
      students.insert(pos, std::move(name));
    }
  }
}

vector<string> school::grade(int grade) const {
  auto it = roster_.find(grade);
  return it == roster_.end() ? vector<string>{} : it->second;
}
} // namespace grade_school