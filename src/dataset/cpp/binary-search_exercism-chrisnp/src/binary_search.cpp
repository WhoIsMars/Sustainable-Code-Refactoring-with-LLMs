#include "binary_search.h"
#include <cassert>
#include <algorithm>
#include <stdexcept>

using std::vector;

int binary_search::find( const vector<int>& haystaq, const int& needle ) {
    assert( is_sorted( haystaq.cbegin(), haystaq.cend() ) );

    long lo { 0L }, hi { static_cast<long>(haystaq.size() - 1) };
    while( lo <= hi ) {
        int mid = (lo + hi) >> 1;
        if( haystaq.at(mid) == needle ) return mid;
        if( haystaq.at(mid) < needle ) lo = mid + 1;
        if( haystaq.at(mid) > needle ) hi = mid - 1;
    }
    throw std::domain_error("not found");
}
