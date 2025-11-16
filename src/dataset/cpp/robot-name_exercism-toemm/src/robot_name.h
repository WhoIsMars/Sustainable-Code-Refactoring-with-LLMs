#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>

namespace robot_name {


    class robot {

        public:

        robot();
        const std::string name() const;
        void reset();

        private:
        std::string _name;
        std::unordered_set<std::string> _names_list;

        void generate_name();

    };
}  // namespace robot_name

#endif  // ROBOT_NAME_H