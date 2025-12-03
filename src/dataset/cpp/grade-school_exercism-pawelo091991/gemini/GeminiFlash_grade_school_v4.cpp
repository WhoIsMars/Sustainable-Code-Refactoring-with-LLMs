#include "grade_school.h"
#include <algorithm>

namespace grade_school {

	const map<int, vector<string>>& school::roster() const {
		return database;
	}

	void school::add(const string& name, int grade) {
		auto& grade_list = database[grade];
		grade_list.push_back(name);
		std::sort(grade_list.begin(), grade_list.end());
	}

	const vector<string>& school::grade(int grade) const {
		auto it = database.find(grade);
		if (it != database.end()) {
			return it->second;
		} else {
			static const vector<string> empty_vector;
			return empty_vector;
		}
	}
}