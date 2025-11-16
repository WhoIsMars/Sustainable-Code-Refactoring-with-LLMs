#include "grade_school.h"

namespace grade_school {
	const map<int, vector<string>>& school::roster() const {
		return database;
	}

	void school::add(const string& name, int grade) {
		auto& grade_vector = database[grade];
		auto insert_pos = std::lower_bound(grade_vector.begin(), grade_vector.end(), name);
		grade_vector.insert(insert_pos, name);
	}

	const vector<string> school::grade(int grade) const {
		auto it = database.find(grade);
		return (it != database.end()) ? it->second : vector<string>{};
	}
}