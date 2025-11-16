#include "grade_school.h"

#include <map>
#include <vector>
#include <algorithm>
#include <string>

namespace grade_school {
map<int, vector<string>> school::roster() const { 
    return class_roster; 
}

void school::add(const string& name, int grade) {
    auto& students = class_roster[grade];
    if (find(students.begin(), students.end(), name) == students.end()) {
        students.emplace_back(name);
        sort(students.begin(), students.end());
    }
}

vector<string> school::grade(int grade) const {
    auto it = class_roster.find(grade);
    return it != class_roster.end() ? it->second : vector<string>{};
}
}  // namespace grade_school