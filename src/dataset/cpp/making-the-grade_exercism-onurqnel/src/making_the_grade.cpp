#include <array>
#include <string>
#include <vector>

// Round down all provided student scores.
std::vector<int> round_down_scores(std::vector<double> student_scores)
{
    std::vector<int> grades;
    for (double score : student_scores)
    {
        grades.push_back(static_cast<int>(score));
    }
    return grades;
}

// Count the number of failing students out of the group provided.
int count_failed_students(std::vector<int> student_scores)
{
    int fail_count = 0;
    for (int score : student_scores)
    {
        if (score <= 40)
        {
            ++fail_count;
        }
    }
    return fail_count;
}

// Determine how many of the provided student scores were 'the best' based on the provided threshold.
std::vector<int> above_threshold(std::vector<int> student_scores, int threshold)
{
    std::vector<int> bests;
    for (int score : student_scores)
    {
        if (score >= threshold)
        {
            bests.push_back(score);
        }
    }
    return bests;
}

// Create a list of grade thresholds based on the provided highest grade.
std::array<int, 4> letter_grades(int highest_score)
{
    int failGrade = 40;
    int letterCount = 4; // Expecting 4 intervals
    int interval = (highest_score - failGrade) / letterCount;

    std::array<int, 4> gradeInterval;

    for (size_t i = 0; i < letterCount; i++)
    {
        gradeInterval[i] = failGrade + (interval * i) + 1;
    }

    return gradeInterval;
}

// Organize the student's rank, name, and grade information in ascending order.
std::vector<std::string> student_ranking(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    std::vector<std::string> results;
    for (size_t i = 0; i < student_scores.size(); i++)
    {
        std::string record = std::to_string(i + 1) + ". " + student_names[i] + ": " + std::to_string(student_scores[i]);
        results.push_back(record);
    }
    return results;
}

// Create a string that contains the name of the first student to make a perfect score on the exam.
std::string perfect_score(std::vector<int> student_scores, std::vector<std::string> student_names)
{
    for (size_t i = 0; i < student_scores.size(); i++)
    {
        if (student_scores[i] == 100)
        {
            return student_names[i];
        }
    }
    return "";
}
