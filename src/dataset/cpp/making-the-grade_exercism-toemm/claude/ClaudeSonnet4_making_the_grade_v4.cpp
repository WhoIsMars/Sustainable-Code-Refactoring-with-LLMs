#include <array>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> round_down_scores(std::vector<double> student_scores) {
    std::vector<int> rounded_down_scores;
    rounded_down_scores.reserve(student_scores.size());
    
    for (const double score : student_scores) {
        rounded_down_scores.push_back(static_cast<int>(score));
    }
    
    return rounded_down_scores;
}

int count_failed_students(std::vector<int> student_scores) {
    return std::count_if(student_scores.begin(), student_scores.end(), 
                        [](int score) { return score <= 40; });
}

std::array<int, 4> letter_grades(int highest_score) {
    const int interval = (highest_score - 40) / 4;
    return {41, 41 + interval, 41 + 2 * interval, 41 + 3 * interval};
}

std::vector<std::string> student_ranking(
    std::vector<int> student_scores, std::vector<std::string> student_names) {
    
    std::vector<std::string> results;
    results.reserve(student_scores.size());
    
    const size_t size = student_scores.size();
    for (size_t i = 0; i < size; ++i) {
        results.push_back(std::to_string(i + 1) + ". " + student_names[i] + ": " + 
                         std::to_string(student_scores[i]));
    }
    
    for (const std::string& str : results) {
        std::cout << str << std::endl;
    }
    
    return results;
}

std::string perfect_score(std::vector<int> student_scores,
                          std::vector<std::string> student_names) {
    
    const size_t size = student_scores.size();
    for (size_t i = 0; i < size; ++i) {
        if (student_scores[i] == 100) {
            return student_names[i];
        }
    }
    
    return "";
}