#include <array>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> round_down_scores(std::vector<double> student_scores)
{
    std::vector<int> rounded_scores;
    rounded_scores.reserve(student_scores.size());
    for (const double& score : student_scores)
    {
        rounded_scores.push_back(static_cast<int>(score));
    }
    return rounded_scores;
}

int count_failed_students(std::vector<int> student_scores)
{
    return std::count_if(student_scores.begin(), student_scores.end(), 
                        [](int score) { return score <= 40; });
}

std::vector<int> above_threshold(std::vector<int> student_scores, int threshold)
{
    std::vector<int> scores_above;
    scores_above.reserve(student_scores.size());
    std::copy_if(student_scores.begin(), student_scores.end(), 
                 std::back_inserter(scores_above),
                 [threshold](int score) { return score >= threshold; });
    return scores_above;
}

std::array<int, 4> letter_grades(int highest_score)
{
    std::array<int, 4> thresholds;
    const int interval = (highest_score - 40) / 4;
    for (int i = 0; i < 4; ++i)
    {
        thresholds[i] = 41 + i * interval;
    }
    return thresholds;
}

std::vector<std::string> student_ranking(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    std::vector<std::string> rankings;
    rankings.reserve(student_scores.size());
    const size_t size = std::min(student_scores.size(), student_names.size());
    for (size_t i = 0; i < size; ++i)
    {
        rankings.push_back(std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]));
    }
    return rankings;
}

std::string perfect_score(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    const size_t size = std::min(student_scores.size(), student_names.size());
    for (size_t i = 0; i < size; ++i)
    {
        if (student_scores[i] == 100)
        {
            return student_names[i];
        }
    }
    return "";
}