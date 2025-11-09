#include <algorithm>
#include <array>
#include <string>
#include <vector>

const int fail_threshold = 40;

// Round down all provided student scores.
std::vector<int> round_down_scores(const std::vector<double>& student_scores) {
    std::vector<int> rounded_scores;
    rounded_scores.reserve(student_scores.size());
    for (double score : student_scores)
        rounded_scores.push_back(static_cast<int>(score));
    return rounded_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(const std::vector<int>& student_scores) {
    return std::count_if(student_scores.begin(), student_scores.end(), [](int score) {
        return score <= fail_threshold;
    });
}

// Determine how many of the provided student scores were 'the best' based on the provided threshold.
std::vector<int> above_threshold(const std::vector<int>& student_scores, int threshold) {
    std::vector<int> best_scores;
    for (int score : student_scores) {
        if (score >= threshold)
            best_scores.push_back(score);
    }
    return best_scores;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score) {
    int grade_range = (highest_score - fail_threshold) / 4;
    return {fail_threshold + 1, fail_threshold + grade_range + 1, fail_threshold + 2 * grade_range + 1, fail_threshold + 3 * grade_range + 1};
}

// Organize the student's rank, name, and grade information in descending order.
std::vector<std::string> student_ranking(const std::vector<int>& student_scores, const std::vector<std::string>& student_names) {
    std::vector<std::string> rankings;
    rankings.reserve(student_names.size());
    for (size_t i = 0; i < student_names.size(); ++i) {
        rankings.emplace_back(std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]));
    }
    return rankings;
}

// Create a string that contains the name of the first student to make a perfect score on the exam.
std::string perfect_score(const std::vector<int>& student_scores, const std::vector<std::string>& student_names) {
    const int perfect = 100;
    auto it = std::find(student_scores.begin(), student_scores.end(), perfect);
    if (it != student_scores.end()) {
        return student_names[std::distance(student_scores.begin(), it)];
    }
    return "";
}