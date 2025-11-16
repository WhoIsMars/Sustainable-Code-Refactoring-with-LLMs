#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

using namespace std;

grade_school::Roster grade_school::school::roster() const {
    return school_;
}

void grade_school::school::add(string student, int grade) {
    auto& students = school_[grade];
    auto it = lower_bound(students.begin(), students.end(), student);
    students.insert(it, student);
}

vector<string> grade_school::school::grade(int grade) const {
    auto it = school_.find(grade);
    if (it != school_.end()) {
        return it->second;
    }
    return {};
}