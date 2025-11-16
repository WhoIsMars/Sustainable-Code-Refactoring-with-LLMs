#include "grade_school.h"

namespace grade_school {
	void school::add(string name, int grade) {
		auto& grade_students = students[grade];
		auto it = std::lower_bound(grade_students.begin(), grade_students.end(), name);
		if (it == grade_students.end() || *it != name) {
			grade_students.insert(it, std::move(name));
		}
	}

	map<int, vector<string>> school::roster() const {
		return students;
	}

	vector<string> school::grade(int grade) const {
		auto it = students.find(grade);
		return (it != students.end()) ? it->second : vector<string>{};
	}
}  // namespace grade_school