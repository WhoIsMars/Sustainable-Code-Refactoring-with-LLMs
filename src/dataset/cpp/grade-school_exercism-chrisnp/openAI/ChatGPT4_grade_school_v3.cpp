#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

using namespace std;

grade_school::Roster grade_school::school::roster() const {
    return school_;
}

void grade_school::school::add(string student, int grade) {
    auto &students = school_[grade];
    if (find(students.begin(), students.end(), student) == students.end()) {
        students.push_back(move(student));
        inplace_merge(students.begin(), students.end() - 1, students.end());
    }
}

vector<string> grade_school::school::grade(int grade) const {
    auto it = school_.find(grade);
    return it != school_.end() ? it->second : vector<string>{};
}