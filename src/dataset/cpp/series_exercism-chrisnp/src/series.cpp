#include "series.h"
#include <stdexcept>

using std::string;
using std::domain_error;

series::slices_t series::slice(string const &input, luint_t slice_size) {
    if ( slice_size <= 0)
        throw domain_error("enigmatic error for not actually slicing");
    luint_t input_size { input.length() };
    if ( input_size < slice_size ) 
        throw domain_error("cannot slice a string shorter than the slicesize");
    series::slices_t slices {};
    for ( luint_t i = 0UL; i <= input_size - slice_size; ++i ) {
        slices.push_back(input.substr(i, slice_size));
    }  
    return { slices.begin(), slices.end() };
}