#if !defined(BOB_H)
#define BOB_H
#include <string>
using namespace std;
namespace bob {
    std::string hey(std::string input);
    bool isQuestion(string input);
    bool isYelling(string input);
    bool isSilence(string input);
    
}  // namespace bob

#endif // BOB_H