#include "pascals_triangle.h"

#include <iostream>

namespace pascals_triangle {

	Triangle generate_rows(const int number_of_rows) {
		if (number_of_rows <= 0) {
			return Triangle();
		}

		Triangle triangle;
		triangle.reserve(number_of_rows);

		// First row
		triangle.emplace_back(1, 1);

		for (int row_num = 1; row_num < number_of_rows; ++row_num) {
			triangle.emplace_back();
			auto& current_row = triangle.back();
			const auto& prev_row = triangle[row_num - 1];
			
			current_row.reserve(row_num + 1);
			current_row.push_back(1);

			for (int pos = 1; pos < row_num; ++pos) {
				current_row.push_back(prev_row[pos - 1] + prev_row[pos]);
			}
			
			current_row.push_back(1);
		}

		return triangle;
	}
} // namespace pascals_triangle