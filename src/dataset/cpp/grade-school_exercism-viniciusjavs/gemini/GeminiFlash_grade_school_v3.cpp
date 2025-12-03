#include "grade_school.h"
#include <algorithm>
#include <vector>

namespace grade_school {

roster_t const &school::roster() const { return roster_; }

void school::add(string name, int grade) {
  auto &students = roster_[grade];
  auto pos = std::lower_bound(students.begin(), students.end(), name);
  if (pos == students.end() || *pos != name) {
    students.insert(pos, name);
  }
}

vector<string> school::grade(int grade) const {
  auto it = roster_.find(grade);
  if (it == roster_.end()) {
    return {};
  }
  return it->second;
}

} // namespace grade_school