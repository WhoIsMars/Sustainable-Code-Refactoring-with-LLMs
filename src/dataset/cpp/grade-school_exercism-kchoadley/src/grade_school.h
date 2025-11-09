#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H 

#include <map>
#include <vector>

namespace grade_school 
{
    class school 
    {
        private:
            std::map<int, std::vector<std::string>> students;

        public:
            school();
            std::map<int, std::vector<std::string>> roster();
            void add(std::string name, int grade);
            std::vector<std::string> grade(int grade);

    };
}

#endif
