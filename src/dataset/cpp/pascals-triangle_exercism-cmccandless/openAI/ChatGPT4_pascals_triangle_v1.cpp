#include "pascals_triangle.h"

namespace pascals_triangle
{
    std::vector<std::vector<int>> generate_rows(int rowCount)
    {
        if (rowCount <= 0)
        {
            return {};
        }

        std::vector<std::vector<int>> rows(rowCount);
        rows[0] = {1};

        for (int i = 1; i < rowCount; ++i)
        {
            rows[i].resize(i + 1);
            rows[i][0] = rows[i][i] = 1;
            for (int j = 1; j < i; ++j)
            {
                rows[i][j] = rows[i - 1][j - 1] + rows[i - 1][j];
            }
        }

        return rows;
    }
} // namespace pascals_triangle