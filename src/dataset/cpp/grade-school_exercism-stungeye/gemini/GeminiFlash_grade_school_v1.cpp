#include "grade_school.h"

#include <vector>
#include <algorithm>
#include <map>

namespace grade_school {
  void school::add(const std::string& name, int grade) {
    auto& grade_list = grades[grade];
    grade_list.push_back(name);
    std::inplace_merge(grade_list.begin(), grade_list.end() - 1, grade_list.end());
  }

  std::map<int, std::vector<std::string>> school::roster() const {
    return grades;
  }

  std::vector<std::string> school::grade(int grade_number) const {
    auto it = grades.find(grade_number);
    if (it == grades.end()) {
      return {};
    }
    return it->second;
  }
}  // namespace grade_school