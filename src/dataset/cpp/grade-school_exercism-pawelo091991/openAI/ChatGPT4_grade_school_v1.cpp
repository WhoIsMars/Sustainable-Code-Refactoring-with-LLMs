#include "grade_school.h"
#include <algorithm> // for std::sort

namespace grade_school {
	const map<int, vector<string>>& school::roster() const {
		return database;
	}

	void school::add(const string& name, int grade) {
		auto& students = database[grade];
		if (std::find(students.begin(), students.end(), name) == students.end()) {
			students.push_back(name);
			std::sort(students.begin(), students.end());
		}
	}

	vector<string> school::grade(int grade) const {
		auto it = database.find(grade);
		return it != database.end() ? it->second : vector<string>{};
	}
}