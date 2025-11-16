#include "grade_school.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

grade_school::Roster grade_school::school::roster() const {
    return school_;
}

void grade_school::school::add(string student, int grade) {
    school_[grade].insert(school_[grade].end(), student);
    sort(school_[grade].begin(), school_[grade].end());
}

vector<string> grade_school::school::grade(int grade) const {
    try {
        return school_.at(grade);
    }
    catch (const std::logic_error &error) {
        static vector<string> empty_grade {};
        return empty_grade;
    }
}
