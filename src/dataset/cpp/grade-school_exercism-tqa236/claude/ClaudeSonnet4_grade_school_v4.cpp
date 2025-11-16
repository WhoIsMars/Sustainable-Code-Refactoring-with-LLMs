#include "grade_school.h"

#include <algorithm>
#include <map>
#include <vector>

namespace grade_school {

std::map<int, std::vector<std::string>> school::roster() const { 
    return class_roster; 
}

void school::add(std::string name, int grade) {
    auto& students = class_roster[grade];
    auto insert_pos = std::lower_bound(students.begin(), students.end(), name);
    students.insert(insert_pos, std::move(name));
}

std::vector<std::string> school::grade(int grade) const {
    auto it = class_roster.find(grade);
    return it != class_roster.end() ? it->second : std::vector<std::string>{};
}

}  // namespace grade_school