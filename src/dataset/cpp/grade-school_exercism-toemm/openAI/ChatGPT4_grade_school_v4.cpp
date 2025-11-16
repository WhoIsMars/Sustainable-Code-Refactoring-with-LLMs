#include "grade_school.h"

#include <map>
#include <string>
#include <vector>
#include <algorithm>

namespace grade_school {

school::school() = default;

const std::map<int, std::vector<std::string>>& school::roster() const {
    return school_roster;
}

void school::add(std::string name, int grade) {
    auto& roster = school_roster[grade];
    if (std::find(roster.begin(), roster.end(), name) == roster.end()) {
        roster.emplace_back(std::move(name));
        std::sort(roster.begin(), roster.end());
    }
}

const std::vector<std::string> school::grade(int grade_num) const {
    auto it = school_roster.find(grade_num);
    return it != school_roster.end() ? it->second : std::vector<std::string>{};
}

void school::print_roster() const {
    for (const auto& [key, value] : school_roster) {
        std::cout << key << ": ";
        for (const auto& name : value) {
            std::cout << name << ", ";
        }
        std::cout << '\n';
    }
}

}  // namespace grade_school