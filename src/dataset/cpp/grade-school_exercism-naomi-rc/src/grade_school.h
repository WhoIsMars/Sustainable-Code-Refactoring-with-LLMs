#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

namespace grade_school {
	class school {
		public:
			void add(string name, int grade);

			map<int, vector<string>> roster() const;

			vector<string> grade(int grade) const;

	private:

		map<int, vector<string>> students;
	};
}  // namespace grade_school
