#include "grade_school.h"
#include <algorithm>
#include <unordered_map>

namespace grade_school {
    const std::map<int, std::vector<std::string>>& school::roster() const {
        return database;
    }

    void school::add(const std::string& name, int grade) {
        auto& students = database[grade];
        if (std::find(students.begin(), students.end(), name) == students.end()) {
            students.push_back(name);
            std::sort(students.begin(), students.end());
        }
    }

    std::vector<std::string> school::grade(int grade) const {
        auto it = database.find(grade);
        return it != database.end() ? it->second : std::vector<std::string>{};
    }
}