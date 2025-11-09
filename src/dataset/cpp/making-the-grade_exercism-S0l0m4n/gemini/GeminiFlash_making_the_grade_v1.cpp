#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <numeric> // for std::transform

const int fail_threshold = 40;

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores) {
    std::vector<int> rounded_scores(student_scores.size());
    std::transform(student_scores.begin(), student_scores.end(), rounded_scores.begin(), [](double score) {
        return static_cast<int>(score);
    });
    return rounded_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores) {
    return std::count_if(student_scores.begin(), student_scores.end(), [](int score) {
        return score <= fail_threshold;
    });
}

// Determine how many of the provided student scores were 'the best' based on the provided threshold.
std::vector<int> above_threshold(std::vector<int> student_scores, int threshold) {
    std::vector<int> best_scores;
    std::copy_if(student_scores.begin(), student_scores.end(), std::back_inserter(best_scores), [threshold](int score) {
        return score >= threshold;
    });
    return best_scores;
}

// Create a list of grade thresholds based on the provided highest grade.
// Assuming the highest score is 88, the range between this score and the fail
// threshold (40) is divided into four equal ranges, i.e. 48/4 = 12 points in
// each range. Then we have these ranges:
//      40 - 52 : min D grade = 41
//      52 - 64 : min C grade = 53
//      64 - 76 : min B grade = 65
//      76 - 88 : min A grade = 77
std::array<int, 4> letter_grades(int highest_score) {
    int grade_range = (highest_score - fail_threshold) / 4;
    std::array<int, 4> grade_thresholds;
    for (size_t i = 0; i < grade_thresholds.size(); ++i) {
        grade_thresholds[i] = fail_threshold + static_cast<int>(i) * grade_range + 1;
    }
    return grade_thresholds;
}

// Organize the student's rank, name, and grade information in descending order.
// The ranking is a string of the form: `<rank>. <name>: <score>`
// Assume the scores are sorted from highest to lowest, with the names corresponding.
std::vector<std::string> student_ranking(std::vector<int> student_scores, std::vector<std::string> student_names) {
    std::vector<std::string> rankings;
    rankings.reserve(student_names.size()); // Pre-allocate memory
    for (size_t i = 0; i < student_names.size(); ++i) {
        rankings.emplace_back(std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]));
    }
    return rankings;
}

// Create a string that contains the name of the first student to make a perfect score on the exam.
std::string perfect_score(std::vector<int> student_scores, std::vector<std::string> student_names) {
    const int perfect = 100;
    auto it = std::find(student_scores.begin(), student_scores.end(), perfect);
    if (it != student_scores.end()) {
        // Perfect score was found: return student's name
        return student_names[std::distance(student_scores.begin(), it)];
    }
    return "";
}