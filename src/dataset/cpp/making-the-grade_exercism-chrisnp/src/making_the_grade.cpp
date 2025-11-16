#include <array>
#include <string>
#include <vector>

using scores_t = std::vector<int>;
using names_t = std::vector<std::string>;
using grades_t = std::array<int, 4>;

// Round down all provided student scores.
auto round_down_scores(const std::vector<double>& student_scores) -> scores_t {
    scores_t rounded_scores {};
    for (auto score: student_scores) 
        rounded_scores.emplace_back(static_cast<int>(score));
    return rounded_scores;
}
// Count the number of failing students out of the group provided.
auto count_failed_students(const scores_t &student_scores) noexcept -> int {
    int count_failed {}, threshold {40};
    for (auto score: student_scores) if (score <= threshold) ++count_failed;
    return count_failed;
}
// Determine how many of the provided student scores were 'the best' based on the provided threshold.
auto above_threshold(const scores_t &student_scores, 
                     const int &threshold) -> scores_t {
    scores_t passing {};
    for (auto score: student_scores) 
        if (score >= threshold) passing.emplace_back(score);
    return passing;
}
// Create a list of grade thresholds based on the provided highest grade.
auto letter_grades(const int &highest_score) noexcept -> grades_t {
    const int passing_threshold = 41, 
              passed = highest_score - passing_threshold + 1;
    const double low_quartile  = passing_threshold + (passed * 0.25), 
                 mid_quartile  = passing_threshold + (passed * 0.50), 
                 high_quartile = passing_threshold + (passed * 0.75);
    return grades_t {passing_threshold, 
                     static_cast<int>(low_quartile), 
                     static_cast<int>(mid_quartile), 
                     static_cast<int>(high_quartile)};
}
// Organize the student's rank, name, and grade information in ascending order.
auto student_ranking(const scores_t &student_scores, 
                     const names_t &student_names) noexcept -> names_t {
    names_t grade_rank {};
    for (int s { 0 }; s < student_scores.size(); ++s)
        grade_rank.emplace_back(std::to_string(s + 1) + ". " +
                                student_names.at(s) + ": " +
                                std::to_string(student_scores.at(s)));
                             
    return grade_rank;
}
// Create a string that contains the name of the first student to make a perfect score on the exam.
auto perfect_score(const scores_t &student_scores, 
                   const names_t &student_names) noexcept -> std::string {
    for (int i { 0 }; i < student_scores.size(); ++i) 
        if (student_scores.at(i) == 100) return student_names.at(i);
    return "";
}


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
