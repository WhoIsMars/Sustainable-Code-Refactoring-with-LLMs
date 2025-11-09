#include "grade_school.h"

namespace grade_school 
{
    school::school() { }
    std::map<int, std::vector<std::string>> school::roster()
    {
        return students;
    }
    
    void school::add(std::string name, int grade)
    {
        if(students.find(grade) == students.end())
            students[grade] = std::vector<std::string> { name };
        
        else
        {
            std::vector<std::string>& students_in_grade = students[grade];
            const auto it = students_in_grade.begin();

            for (auto iterator = students_in_grade.begin(); iterator < students_in_grade.end(); iterator++) 
            {
                if(name < *iterator)
                {
                    students_in_grade.insert(iterator, name);
                    return;
                }

            }
            
            students_in_grade.push_back(name);
        }

    }
    std::vector<std::string> school::grade(int grade)
    {
        if(students.find(grade) == students.end())
            return std::vector<std::string> { };
        
        return students[grade];

    }
}
