#if !defined(GRADE_SCHOOL_H)
#define GRADE_SCHOOL_H

#include <vector>
#include <map>
#include <string>

namespace grade_school {



    class school {
        public:

        school();
        const std::map<int, std::vector<std::string>>& roster() const;
        void add(std::string name, int grade);
        void print_roster() const;
        const std::vector<std::string> grade(int grade_num) const;

        private:
        std::map<int, std::vector<std::string>> school_roster;


    };
}  // namespace grade_school

#endif  // GRADE_SCHOOL_H