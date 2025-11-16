#include "pascals_triangle.h"

namespace pascals_triangle
{
    std::vector<std::vector<int>> generate_rows(int rowCount)
    {
        if (rowCount <= 0) {
            return {};
        }
        
        std::vector<std::vector<int>> rows;
        rows.reserve(rowCount);
        
        rows.emplace_back(1, 1);
        
        for (int i = 1; i < rowCount; i++)
        {
            const auto& previousRow = rows[i - 1];
            std::vector<int> row;
            row.reserve(i + 1);
            row.push_back(1);
            
            for (int j = 1; j < i; j++)
            {
                row.push_back(previousRow[j - 1] + previousRow[j]);
            }
            
            row.push_back(1);
            rows.push_back(std::move(row));
        }
        
        return rows;
    }
} // namespace pascals_triangle