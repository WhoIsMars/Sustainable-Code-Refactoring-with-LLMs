#include <algorithm>
#include <array>
#include <string>
#include <vector>

const int fail_threshold = 40;

std::vector<int> round_down_scores(const std::vector<double>& student_scores) {
    std::vector<int> rounded_scores(student_scores.size());
    std::transform(student_scores.begin(), student_scores.end(), rounded_scores.begin(),
                   [](double score) { return static_cast<int>(score); });
    return rounded_scores;
}

int count_failed_students(const std::vector<int>& student_scores) {
    return std::count_if(student_scores.begin(), student_scores.end(),
                         [](int score) { return score <= fail_threshold; });
}

std::vector<int> above_threshold(const std::vector<int>& student_scores, int threshold) {
    std::vector<int> best_scores;
    std::copy_if(student_scores.begin(), student_scores.end(), std::back_inserter(best_scores),
                 [threshold](int score) { return score >= threshold; });
    return best_scores;
}

std::array<int, 4> letter_grades(int highest_score) {
    int grade_range = (highest_score - fail_threshold) / 4;
    return {fail_threshold + 1, fail_threshold + grade_range + 1,
            fail_threshold + 2 * grade_range + 1, fail_threshold + 3 * grade_range + 1};
}

std::vector<std::string> student_ranking(const std::vector<int>& student_scores, const std::vector<std::string>& student_names) {
    std::vector<std::string> rankings(student_scores.size());
    for (size_t i = 0; i < student_scores.size(); ++i) {
        rankings[i] = std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]);
    }
    return rankings;
}

std::string perfect_score(const std::vector<int>& student_scores, const std::vector<std::string>& student_names) {
    const int perfect = 100;
    auto it = std::find(student_scores.begin(), student_scores.end(), perfect);
    return (it != student_scores.end()) ? student_names[std::distance(student_scores.begin(), it)] : "";
}