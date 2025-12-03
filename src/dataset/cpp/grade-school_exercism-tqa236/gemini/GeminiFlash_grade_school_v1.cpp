#include "grade_school.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace grade_school {
map<int, vector<string> > school::roster() const { return class_roster; }

void school::add(string name, int grade) {
  auto it = class_roster.find(grade);
  if (it == class_roster.end()) {
    class_roster.insert({grade, {name}});
  } else {
    auto& students = it->second;
    students.push_back(name);
    sort(students.begin(), students.end());
  }
}

vector<string> school::grade(int grade) const {
  auto it = class_roster.find(grade);
  if (it == class_roster.end()) {
    return {};
  } else {
    return it->second;
  }
}
}  // namespace grade_school