#include "grade_school.h"

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

namespace grade_school {
map<int, vector<string>> school::roster() const { 
    return class_roster; 
}

void school::add(string name, int grade) {
    auto& students = class_roster[grade];
    if (find(students.begin(), students.end(), name) == students.end()) {
        students.push_back(move(name));
        sort(students.begin(), students.end());
    }
}

vector<string> school::grade(int grade) const {
    auto it = class_roster.find(grade);
    return it != class_roster.end() ? it->second : vector<string>{};
}
}  // namespace grade_school