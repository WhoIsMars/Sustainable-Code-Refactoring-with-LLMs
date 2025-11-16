#include "grade_school.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace grade_school {
map<int, vector<string> > school::roster() const { return class_roster; }
void school::add(string name, int grade) {
  if (class_roster.find(grade) == class_roster.end()) {
    class_roster.insert(pair<int, vector<string> >(grade, {name}));
  } else {
    auto& students = class_roster[grade];
    students.push_back(name);
    sort(begin(students), end(students));
  }
}
vector<string> school::grade(int grade) const {
  if (class_roster.find(grade) == class_roster.end()) {
    return {};
  } else {
    auto aux = class_roster.find(grade)->second;
    return aux;
  }
}
}  // namespace grade_school
