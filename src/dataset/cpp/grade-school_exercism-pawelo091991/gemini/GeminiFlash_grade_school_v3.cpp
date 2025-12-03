#include "grade_school.h"
#include <algorithm>
#include <vector>
#include <map>

namespace grade_school {

	const std::map<int, std::vector<std::string>> school::roster() const {
		return database;
	}

	void school::add(const std::string& name, int grade) {
		auto& grade_list = database[grade];
		grade_list.push_back(name);
		std::sort(grade_list.begin(), grade_list.end());
	}

	const std::vector<std::string> school::grade(int grade) const {
		auto it = database.find(grade);
		if (it != database.end()) {
			return it->second;
		}
		else {
			return {};
		}
	}
}