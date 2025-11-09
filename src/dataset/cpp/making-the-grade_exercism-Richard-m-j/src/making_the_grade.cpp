#include <array>
#include <string>
#include <vector>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores)
{
    // TODO: Implement round_down_scores
    std::vector<int> rounded_scores;
    for (int i = 0; i < student_scores.size(); i++)
        rounded_scores.push_back(static_cast<int>(student_scores[i]));

    return rounded_scores;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores)
{
    // TODO: Implement count_failed_students
    int failed_students = 0;
    for (int i = 0; i < student_scores.size(); i++)
        if (student_scores[i] < 48)
            failed_students++;
    return failed_students;
}

// Determine how many of the provided student scores were 'the best' based on the provided threshold.
std::vector<int> above_threshold(std::vector<int> student_scores, int threshold)
{
    // TODO: Implement above_threshold
    std::vector<int> above_threshold;
    for (int i = 0; i < student_scores.size(); i++)
        if (student_scores[i] >= 48)
            above_threshold.push_back(student_scores[i]);
    return above_threshold;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score)
{
    // TODO: Implement above_threshold
    std::array<int, 4> lower_bounds;
    lower_bounds[0] = 48 + 1;
    lower_bounds[1] = lower_bounds[0] + highest_score / 4;
    lower_bounds[2] = lower_bounds[1] + highest_score / 4;
    lower_bounds[3] = lower_bounds[2] + highest_score / 4;
    return lower_bounds;
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    // TODO: Implement student_ranking
    std::vector<std::string> student_ranking;
    for (int i = 0; i < student_scores.size(); i++)
        student_ranking.push_back(std::to_string(i + 1) + student_names[i] + std::to_string(student_scores[i]));
    return student_ranking;
}

// Create a string that contains the name of the first student to make a perfect score on the exam.
std::string perfect_score(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    // TODO: Implement perfect_score
    for (int i = 0; i < student_scores.size(); i++)
        if (student_scores[i] == 100)
            return student_names[i];
    return "";
}