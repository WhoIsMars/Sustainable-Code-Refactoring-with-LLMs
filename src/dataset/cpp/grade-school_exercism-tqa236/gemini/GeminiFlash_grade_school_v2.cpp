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
    class_roster.emplace(grade, vector<string>{name});
  } else {
    it->second.push_back(name);
    sort(it->second.begin(), it->second.end());
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