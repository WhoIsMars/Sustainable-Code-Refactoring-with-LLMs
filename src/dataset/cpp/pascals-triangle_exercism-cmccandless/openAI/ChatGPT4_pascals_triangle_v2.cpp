#include "pascals_triangle.h"

namespace pascals_triangle
{
    std::vector<std::vector<int>> generate_rows(int rowCount)
    {
        std::vector<std::vector<int>> rows;
        if (rowCount > 0)
        {
            rows.reserve(rowCount); // Reserve memory upfront to avoid reallocations
            rows.push_back({1});
            for (int i = 1; i < rowCount; i++)
            {
                const std::vector<int>& previousRow = rows.back();
                std::vector<int> row(i + 1, 1); // Initialize row with 1s
                for (int j = 1; j < i; j++)
                {
                    row[j] = previousRow[j - 1] + previousRow[j];
                }
                rows.push_back(std::move(row)); // Use move semantics to avoid copying
            }
        }
        return rows;
    }
} // namespace pascals_triangle