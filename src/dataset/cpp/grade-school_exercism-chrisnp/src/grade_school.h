#pragma once

#include <string>
#include <vector>
#include <map>

namespace grade_school {

using Roster = std::map<int, std::vector<std::string>>;

class school {
public:
    Roster roster() const;
    void add(std::string, int);
    std::vector<std::string> grade(int) const;
private:
    Roster school_;
}; // class school
}  // namespace grade_school

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif