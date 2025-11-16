#include "grade_school.h"
#include <algorithm>

namespace grade_school {
	void school::add(string name, int grade) {
		auto& grade_students = students[grade];
		if (!binary_search(grade_students.begin(), grade_students.end(), name)) {
			grade_students.insert(lower_bound(grade_students.begin(), grade_students.end(), name), name);
		}
	}

	map<int, vector<string>> school::roster() const {
		return students;
	}

	vector<string> school::grade(int grade) const {
		auto it = students.find(grade);
		return it != students.end() ? it->second : vector<string>{};
	}
}  // namespace grade_school