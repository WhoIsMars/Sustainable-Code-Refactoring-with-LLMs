#include "grade_school.h"
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;
using namespace grade_school;

map<int, set<string>> grades;

map<int, vector<string>> school::roster()
{
    map<int, vector<string>> result;
    for (const auto& [grade, names] : grades) {
        result[grade] = vector<string>(names.begin(), names.end());
    }
    return result;
}

void school::add(string n, int no)
{
    grades[no].insert(move(n));
}

vector<string> school::grade(int n)
{
    if (grades.find(n) != grades.end()) {
        return vector<string>(grades[n].begin(), grades[n].end());
    }
    return {};
}