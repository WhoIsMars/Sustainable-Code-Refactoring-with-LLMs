#include "grade_school.h"

#include <vector>
#include <algorithm>
#include <map>

namespace grade_school {
  void school::add(const std::string& name, int grade) {
    auto& students = grades[grade];
    if (std::find(students.begin(), students.end(), name) == students.end()) {
      students.insert(std::upper_bound(students.begin(), students.end(), name), name);
    }
  }

  const std::map<int, std::vector<std::string>>& school::roster() const {
    return grades;
  }

  std::vector<std::string> school::grade(int grade_number) const {
    auto it = grades.find(grade_number);
    return it != grades.end() ? it->second : std::vector<std::string>();
  }
}  // namespace grade_school