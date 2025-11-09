#include <algorithm>
#include <array>
#include <string>
#include <vector>

const int fail_threshold = 40;

std::vector<int> round_down_scores(std::vector<double> student_scores) {
    std::vector<int> rounded_scores;
    rounded_scores.reserve(student_scores.size());
    for (const auto& score : student_scores) {
        rounded_scores.push_back(static_cast<int>(score));
    }
    return rounded_scores;
}

int count_failed_students(std::vector<int> student_scores) {
    return std::count_if(student_scores.begin(), student_scores.end(),
                        [](int score) { return score <= fail_threshold; });
}

std::vector<int> above_threshold(std::vector<int> student_scores, int threshold) {
    std::vector<int> best_scores;
    best_scores.reserve(student_scores.size());
    std::copy_if(student_scores.begin(), student_scores.end(),
                std::back_inserter(best_scores),
                [threshold](int score) { return score >= threshold; });
    return best_scores;
}

std::array<int, 4> letter_grades(int highest_score) {
    const int grade_range = (highest_score - fail_threshold) / 4;
    std::array<int, 4> grade_thresholds;
    for (size_t i = 0; i < grade_thresholds.size(); ++i) {
        grade_thresholds[i] = fail_threshold + static_cast<int>(i) * grade_range + 1;
    }
    return grade_thresholds;
}

std::vector<std::string> student_ranking(std::vector<int> student_scores, std::vector<std::string> student_names) {
    std::vector<std::string> rankings;
    rankings.reserve(student_names.size());
    for (size_t i = 0; i < student_names.size(); ++i) {
        rankings.emplace_back(std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]));
    }
    return rankings;
}

std::string perfect_score(std::vector<int> student_scores, std::vector<std::string> student_names) {
    constexpr int perfect = 100;
    const auto it = std::find(student_scores.begin(), student_scores.end(), perfect);
    if (it != student_scores.end()) {
        const auto index = std::distance(student_scores.begin(), it);
        return student_names[index];
    }
    return "";
}