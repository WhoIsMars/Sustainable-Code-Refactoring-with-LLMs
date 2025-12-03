#include "grade_school.h"
#include <algorithm>
#include <vector>

namespace grade_school {

roster_t const &school::roster() const { return roster_; }

void school::add(string name, int grade) {
  roster_[grade].push_back(std::move(name));
  std::sort(roster_[grade].begin(), roster_[grade].end());
}

vector<string> school::grade(int grade) const {
  auto it = roster_.find(grade);
  if (it == roster_.end()) {
    return {};
  }
  return it->second;
}

} // namespace grade_school