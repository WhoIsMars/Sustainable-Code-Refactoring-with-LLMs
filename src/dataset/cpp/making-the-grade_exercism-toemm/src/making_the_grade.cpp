#include <array>
#include <string>
#include <vector>
#include <iostream>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores) {
    
    std::vector<int> rounded_down_scores{};

    for (double score : student_scores) {

        rounded_down_scores.push_back(static_cast<int>(score));

    }

    return rounded_down_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores) {
    
    int i{};

    for (std::vector<int>::iterator it{student_scores.begin()}; it != student_scores.end(); ++it) {
        if (*it <= 40) { // Dereference Iterator to get value
            i++;
        }
    }
    
    
    return i;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score) {

    int intervall{(highest_score-40) / 4};

    return {41, 41+intervall, 41+2*intervall, 41+3*intervall};
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(
    std::vector<int> student_scores, std::vector<std::string> student_names) {

        std::vector<std::string> results {};

        for (int i {0}; i < student_scores.size(); ++i)
        {

            results.push_back(std::to_string(i+1) + ". " + student_names.at(i) + ": " + 
                              std::to_string(student_scores[i]));
        }

        for (std::string& str : results)
        {
            std::cout << str << std::endl;
        }
    return results;
}

// Create a string that contains the name of the first student to make a perfect
// score on the exam.
std::string perfect_score(std::vector<int> student_scores,
                          std::vector<std::string> student_names) {

    for (int i=0; i < student_scores.size(); i++)
    {
        if (student_scores[i] == 100) 
        {
            return student_names[i];
        }
    }                               

    return "";
}
