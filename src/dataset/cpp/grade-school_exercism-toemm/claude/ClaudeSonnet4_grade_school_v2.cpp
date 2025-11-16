#include "grade_school.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace grade_school {

school::school() { }

const std::map<int, std::vector<std::string>>& school::roster() const { 
    return this->school_roster; 
}

void school::add(std::string name, int grade) {
    auto it = school_roster.find(grade);
    if (it == school_roster.end()) {
        school_roster[grade] = {std::move(name)};
    } else {
        auto& roster = it->second;
        auto insert_pos = std::lower_bound(roster.begin(), roster.end(), name);
        roster.insert(insert_pos, std::move(name));
    }
}

const std::vector<std::string> school::grade(int grade_num) const {
    auto it = school_roster.find(grade_num);
    return (it != school_roster.end()) ? it->second : std::vector<std::string>{};
}

void school::print_roster() const {
    for (const auto& [key, value] : this->school_roster) {
        std::cout << key << ": ";
        for (const auto& name: value) {
            std::cout << name << ", ";
        }
        std::cout << std::endl;
    }
}

}  // namespace grade_school