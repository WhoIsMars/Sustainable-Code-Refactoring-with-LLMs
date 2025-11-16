#include "grade_school.h"

namespace grade_school {
	void school::add(string name, int grade) {		
		students[grade].insert(upper_bound(students[grade].begin(), students[grade].end(), name), name);
	}

	map<int, vector<string>> school::roster() const {		
		return students;
	}

	vector<string> school::grade(int grade) const {
		auto position = students.find(grade);
		if (position == students.end())
			return {};
		return position->second;
	}
}  // namespace grade_school
