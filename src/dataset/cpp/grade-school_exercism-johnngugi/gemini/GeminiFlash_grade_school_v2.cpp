#include "grade_school.h"
#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;
using namespace grade_school;

map<int, vector<string>> school::roster() const
{
    return grades;
}

void school::add(const string& name, int grade)
{
    grades[grade].push_back(name);
    sort(grades[grade].begin(), grades[grade].end());
}

vector<string> school::grade(int grade) const
{
    auto it = grades.find(grade);
    if (it != grades.end()) {
        return it->second;
    } else {
        return {};
    }
}