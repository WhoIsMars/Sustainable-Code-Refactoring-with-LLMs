#include "grade_school.h"

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

namespace grade_school {
const map<int, vector<string>>& school::roster() const { return class_roster; }

void school::add(string name, int grade) {
  auto& students = class_roster[grade];
  auto insert_pos = lower_bound(students.begin(), students.end(), name);
  students.insert(insert_pos, move(name));
}

vector<string> school::grade(int grade) const {
  auto it = class_roster.find(grade);
  return (it != class_roster.end()) ? it->second : vector<string>{};
}
}  // namespace grade_school