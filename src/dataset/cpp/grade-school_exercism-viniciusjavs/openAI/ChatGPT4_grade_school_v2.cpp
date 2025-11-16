#include "grade_school.h"
#include <algorithm>
#include <map>
#include <vector>
#include <string>

namespace grade_school {
roster_t const &school::roster() const { return roster_; }

void school::add(const string &name, int grade) {
  auto &students = roster_[grade];
  if (std::find(cbegin(students), cend(students), name) == cend(students)) {
    students.emplace_back(name);
    std::sort(begin(students), end(students));
  }
}

vector<string> school::grade(int grade) const {
  auto it = roster_.find(grade);
  return it != roster_.end() ? it->second : vector<string>{};
}
} // namespace grade_school