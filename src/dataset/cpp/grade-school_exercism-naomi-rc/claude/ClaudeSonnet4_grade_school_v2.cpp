#include "grade_school.h"

namespace grade_school {
	void school::add(string name, int grade) {		
		auto& grade_students = students[grade];
		grade_students.insert(
			std::lower_bound(grade_students.begin(), grade_students.end(), name), 
			std::move(name)
		);
	}

	map<int, vector<string>> school::roster() const {		
		return students;
	}

	vector<string> school::grade(int grade) const {
		auto position = students.find(grade);
		return position != students.end() ? position->second : vector<string>{};
	}
}  // namespace grade_school