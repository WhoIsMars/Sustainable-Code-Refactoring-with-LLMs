#include "grade_school.h"
#include <algorithm>
#include <utility>

namespace grade_school {
	const map<int, vector<string>>& school::roster() const {
		return database;
	}

	void school::add(string name, int grade) {
		auto& students = database[grade];
		auto it = std::lower_bound(students.begin(), students.end(), name);
		students.insert(it, std::move(name));
	}

	vector<string> school::grade(int grade) const {
		auto it = database.find(grade);
		return it != database.end() ? it->second : vector<string>{};
	}
}