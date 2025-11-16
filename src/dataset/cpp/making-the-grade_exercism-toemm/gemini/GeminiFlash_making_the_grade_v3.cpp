#include <array>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores) {
    std::vector<int> rounded_down_scores(student_scores.size());
    std::transform(student_scores.begin(), student_scores.end(), rounded_down_scores.begin(),
                   [](double score) { return static_cast<int>(score); });
    return rounded_down_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores) {
    return std::count_if(student_scores.begin(), student_scores.end(), [](int score) { return score <= 40; });
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score) {
    int interval = (highest_score - 40) / 4;
    return {41, 41 + interval, 41 + 2 * interval, 41 + 3 * interval};
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(
    std::vector<int> student_scores, std::vector<std::string> student_names) {

    std::vector<std::string> results;
    results.reserve(student_scores.size());

    for (size_t i = 0; i < student_scores.size(); ++i) {
        results.emplace_back(std::to_string(i + 1) + ". " + student_names[i] + ": " +
                             std::to_string(student_scores[i]));
        std::cout << results.back() << std::endl;
    }

    return results;
}

// Create a string that contains the name of the first student to make a perfect
// score on the exam.
std::string perfect_score(std::vector<int> student_scores,
                          std::vector<std::string> student_names) {
    for (size_t i = 0; i < student_scores.size(); ++i) {
        if (student_scores[i] == 100) {
            return student_names[i];
        }
    }

    return "";
}