#if !defined(PRIME_FACTORS_H)
#define PRIME_FACTORS_H
#include <vector>
using namespace std;
namespace prime_factors
{
    vector<int> of(int n);
    void factor(int n, vector<int> &result);

} // namespace prime_factors

#endif // PRIME_FACTORS_H