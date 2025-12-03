#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

// Round down all provided student scores.
std::vector<int> round_down_scores(const std::vector<double>& student_scores)
{
    std::vector<int> rounded_scores(student_scores.size());
    std::transform(student_scores.begin(), student_scores.end(), rounded_scores.begin(), [](double score) {
        return static_cast<int>(score);
    });
    return rounded_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(const std::vector<int>& student_scores)
{
    return std::count_if(student_scores.begin(), student_scores.end(), [](int score) {
        return score <= 40;
    });
}

// Determine how many of the provided student scores were 'the best' based on the provided threshold.
std::vector<int> above_threshold(const std::vector<int>& student_scores, int threshold)
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
    std::iota(thresholds.begin(), thresholds.end(), 0);
    std::transform(thresholds.begin(), thresholds.end(), thresholds.begin(), [interval](int i) {
        return 41 + i * interval;
    });
    return thresholds;
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(const std::vector<int>& student_scores, const std::vector<std::string>& student_names)
{
    std::vector<std::pair<int, std::string>> students(student_scores.size());
    for (size_t i = 0; i < student_scores.size(); ++i)
    {
        students[i] = {student_scores[i], student_names[i]};
    }

    std::sort(students.begin(), students.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    std::vector<std::string> rankings;
    rankings.reserve(students.size());
    for (size_t i = 0; i < students.size(); ++i)
    {
        rankings.push_back(std::to_string(i + 1) + ". " + students[i].second + ": " + std::to_string(students[i].first));
    }
    return rankings;
}

// Create a string that contains the name of the first student to make a perfect score on the exam.
std::string perfect_score(const std::vector<int>& student_scores, const std::vector<std::string>& student_names)
{
    auto it = std::find(student_scores.begin(), student_scores.end(), 100);
    if (it != student_scores.end())
    {
        return student_names[std::distance(student_scores.begin(), it)];
    }
    return "";
}