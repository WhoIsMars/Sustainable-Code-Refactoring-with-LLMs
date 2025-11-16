#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <set>

using namespace std;

grade_school::Roster grade_school::school::roster() const {
    return school_;
}

void grade_school::school::add(string student, int grade) {
    auto& students = school_[grade];
    if (!binary_search(students.begin(), students.end(), student)) {
        students.insert(lower_bound(students.begin(), students.end(), student), student);
    }
}

vector<string> grade_school::school::grade(int grade) const {
    auto it = school_.find(grade);
    if (it != school_.end()) {
        return it->second;
    }
    return {};
}