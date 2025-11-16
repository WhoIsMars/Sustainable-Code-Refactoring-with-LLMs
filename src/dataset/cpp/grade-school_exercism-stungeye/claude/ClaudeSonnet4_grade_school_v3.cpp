#include "grade_school.h"

#include <vector>
#include <algorithm>

namespace grade_school {
  void school::add(const std::string& name, int grade) {
    auto& grade_list = grades[grade];
    auto insert_pos = std::lower_bound(grade_list.begin(), grade_list.end(), name);
    grade_list.insert(insert_pos, name);
  }

  std::map<int, std::vector<std::string>> school::roster() const {
    return grades;
  }

  std::vector<std::string> school::grade(int grade_number) const {
    auto it = grades.find(grade_number);
    if (it == grades.end()) {
      return std::vector<std::string>();
    }
    return it->second;
  }
}  // namespace grade_school