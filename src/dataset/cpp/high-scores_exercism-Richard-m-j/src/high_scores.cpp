#include "high_scores.h"

#include <algorithm>

namespace arcade
{

    std::vector<int> HighScores::list_scores()
    {
        // TODO: Return all scores for this session.
        return scores;
    }

    int HighScores::latest_score()
    {
        // TODO: Return the latest score for this session.
        int latest;
        for (auto num : scores)
            latest = num;
        return latest;
    }

    int HighScores::personal_best()
    {
        // TODO: Return the highest score for this session.
        int best;
        for (auto num : scores)
            if (best < num)
                best = num;
        return best;
    }

    std::vector<int> HighScores::top_three()
    {
        // TODO: Return the top 3 scores for this session in descending order.
        int a = 0, b = 0, c = 0;

        for (auto num : scores)
            if (num >= a)
            {
                c = b;
                b = a;
                a = num;
            }
            else if (num >= b)
            {
                c = b;
                b = num;
            }
            else if (num >= c)
                c = num;

        if (b == 0 && c == 0)
            return {a};
        if (c == 0)
            return {a, b};
        return {a, b, c};
    }

} // namespace arcade
