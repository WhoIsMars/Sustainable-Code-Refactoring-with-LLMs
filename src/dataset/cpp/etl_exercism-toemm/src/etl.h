#if !defined(ETL_H)
#define ETL_H

#include <map>
#include <vector>

namespace etl {

using namespace std;


map<char, int> transform(const map<int, vector<char>>& old);


}  // namespace etl

#endif  // ETL_H