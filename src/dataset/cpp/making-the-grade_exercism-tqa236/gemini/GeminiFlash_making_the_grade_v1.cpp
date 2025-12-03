#include <array>
#include <string>
#include <vector>
#include <algorithm>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores)
{
    std::vector<int> rounded_scores;
    rounded_scores.reserve(student_scores.size());
    std::transform(student_scores.begin(), student_scores.end(), std::back_inserter(rounded_scores), [](double score) {
        return static_cast<int>(score);
    });
    return rounded_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores)
{
    return std::count_if(student_scores.begin(), student_scores.end(), [](int score) {
        return score <= 40;
    });
}

// Determine how many of the provided student scores were 'the best' based on the provided threshold.
std::vector<int> above_threshold(std::vector<int> student_scores, int threshold)
{
    std::vector<int> scores_above;
    std::copy_if(student_scores.begin(), student_scores.end(), std::back_inserter(scores_above), [threshold](int score) {
        return score >= threshold;
    });
    return scores_above;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score)
{
    std::array<int, 4> thresholds;
    int interval = (highest_score - 40) / 4;
    for (size_t i = 0; i < thresholds.size(); ++i)
    {
        thresholds[i] = 41 + static_cast<int>(i * interval);
    }
    return thresholds;
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    std::vector<std::pair<int, std::string>> student_data;
    student_data.reserve(student_scores.size());
    for (size_t i = 0; i < student_scores.size(); ++i)
    {
        student_data.emplace_back(student_scores[i], student_names[i]);
    }

    std::sort(student_data.begin(), student_data.end());

    std::vector<std::string> rankings;
    rankings.reserve(student_scores.size());
    for (size_t i = 0; i < student_data.size(); ++i)
    {
        rankings.push_back(std::to_string(i + 1) + ". " + student_data[i].second + ": " + std::to_string(student_data[i].first));
    }
    return rankings;
}

// Create a string that contains the name of the first student to make a perfect score on the exam.
std::string perfect_score(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    for (size_t i = 0; i < student_scores.size(); ++i)
    {
        if (student_scores[i] == 100)
        {
            return student_names[i];
        }
    }
    return "";
}