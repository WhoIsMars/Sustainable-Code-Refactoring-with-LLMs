#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {




class number_class {
    public:
    number_class(const std::string& number);
    std::string number();

    private:
    std::string _number;
    void format_number();


};

number_class phone_number(const std::string& number);


}  // namespace phone_number

#endif  // PHONE_NUMBER_H