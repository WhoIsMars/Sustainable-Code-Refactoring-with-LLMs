#if !defined(BOB_H)
#define BOB_H

#include <string>

namespace bob {

using namespace std;

const string hey(const string& msg);

template<typename T>
bool ends_in_question(const T& msg);


}  // namespace bob

#endif  // BOB_H