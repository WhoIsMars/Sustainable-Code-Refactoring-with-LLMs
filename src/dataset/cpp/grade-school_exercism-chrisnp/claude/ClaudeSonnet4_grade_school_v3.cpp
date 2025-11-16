#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

grade_school::Roster grade_school::school::roster() const {
    return school_;
}

void grade_school::school::add(string student, int grade) {
    auto& grade_list = school_[grade];
    auto insert_pos = lower_bound(grade_list.begin(), grade_list.end(), student);
    grade_list.insert(insert_pos, move(student));
}

vector<string> grade_school::school::grade(int grade) const {
    auto it = school_.find(grade);
    if (it != school_.end()) {
        return it->second;
    }
    static const vector<string> empty_grade;
    return empty_grade;
}