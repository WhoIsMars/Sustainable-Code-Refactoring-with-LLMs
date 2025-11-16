#include "grade_school.h"
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <set>

using namespace std;

grade_school::Roster grade_school::school::roster() const {
    return school_;
}

void grade_school::school::add(string student, int grade) {
    auto& students = school_[grade];
    if (students.insert(student).second) {
        // No need to sort as std::set maintains order
    }
}

vector<string> grade_school::school::grade(int grade) const {
    auto it = school_.find(grade);
    if (it != school_.end()) {
        return vector<string>(it->second.begin(), it->second.end());
    }
    return {};
}