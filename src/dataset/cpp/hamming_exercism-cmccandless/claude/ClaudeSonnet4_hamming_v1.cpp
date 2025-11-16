#include <stdexcept>
#include "hamming.h" 

using namespace std;

int hamming::compute(string a, string b)
{
	if (a.length() != b.length())
	{
		throw domain_error("a.size() != b.size()");
	}
	
	int result = 0;
	const size_t len = a.length();
	const char* ptr_a = a.data();
	const char* ptr_b = b.data();
	
	for (size_t i = 0; i < len; ++i)
	{
		result += ptr_a[i] != ptr_b[i];
	}
	return result;
}