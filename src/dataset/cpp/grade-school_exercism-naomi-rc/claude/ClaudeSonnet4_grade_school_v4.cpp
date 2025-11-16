#include "grade_school.h"

namespace grade_school {
	void school::add(string name, int grade) {
		students[grade].emplace_back(std::move(name));
		std::sort(students[grade].begin(), students[grade].end());
	}

	map<int, vector<string>> school::roster() const {
		return students;
	}

	vector<string> school::grade(int grade) const {
		const auto it = students.find(grade);
		return it != students.end() ? it->second : vector<string>{};
	}
}  // namespace grade_school