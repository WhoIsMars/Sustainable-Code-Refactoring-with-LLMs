#include "bob.h"

using namespace std;

string bob::hey(const string &query) noexcept {
    return  regex_search(query, shout) && regex_search(query, question) 
            ? RESPONSE_EMPHATIC 
            : regex_search(query, shout)    
            ? RESPONSE_SHOUTING 
            : regex_search(query, question) 
            ? RESPONSE_QUESTION 
            : regex_search(query, silence)  
            ? RESPONSE_SILENCE  
            : RESPONSE_DEFAULT;
}
