#include "grade_school.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace grade_school {


school::school() { }

const std::map<int, std::vector<std::string>>& school::roster() const { 
    //print_roster();
    return this->school_roster; 
}



void school::add(std::string name, int grade) {


    auto& roster = school_roster[grade];

    roster.push_back(name);

    std::sort(roster.begin(), roster.end());


    /* if (this->school_roster.find(grade) == this->school_roster.end()) {
        this->school_roster.insert({grade, {name}});

    } else {
        std::vector<std::string>& grade_roster = this->school_roster[grade];

        // check if name of student is already in roster
        for (auto roster_name : grade_roster) {
            if (name == roster_name) return;
        } 

        // add name to the roster
        grade_roster.emplace_back(name);

        // sort roster
        std::sort(grade_roster.begin(), grade_roster.end(),
        [](std::string s1, std::string s2) {
            return s1 < s2;
        });

        this->grade(grade);
    } */

    //print_roster();
}

const std::vector<std::string> school::grade(int grade_num) const {

    if (school_roster.find(grade_num) != school_roster.end()) {
        return school_roster.find(grade_num)->second;
    } else {
        return {};
    }

}


void school::print_roster() const {

    for (auto& [key, value] : this->school_roster) {
        std::cout << key << ": ";
        for (auto& name: value) {
            std::cout << name << ", ";
        }
        std::cout << std::endl;
    }
}



}  // namespace grade_school
