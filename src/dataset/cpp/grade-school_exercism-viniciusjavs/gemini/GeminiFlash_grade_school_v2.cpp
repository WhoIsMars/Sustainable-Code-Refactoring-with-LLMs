#include "grade_school.h"
#include <algorithm>
#include <vector>

namespace grade_school {

const roster_t& school::roster() const { return roster_; }

void school::add(std::string name, int grade) {
  roster_[grade].push_back(std::move(name));
  std::sort(roster_[grade].begin(), roster_[grade].end());
}

std::vector<std::string> school::grade(int grade) const {
  auto it = roster_.find(grade);
  if (it != roster_.end()) {
    return it->second;
  } else {
    return {};
  }
}

} // namespace grade_school