#include "phone_number.h"

#include <stdexcept>
#include <algorithm>

using std::string;

phone_number::phone_number::phone_number(const string &number) {
    string pnumber;
    pnumber.reserve(11); // Reserve space for maximum possible digits
    
    // Extract digits without regex
    for (char c : number) {
        if (c >= '0' && c <= '9') {
            pnumber += c;
        }
    }
    
    auto plength = pnumber.length();
    if (plength < 10) throw std::domain_error { "Less than 10 digits" };
    if (plength > 11) throw std::domain_error { "More than 11 digits" };
    if (plength == 11) {
        if (pnumber[0] == '1') { 
            pnumber.erase(0, 1);
        } else {  
            throw std::domain_error { "Should start with 1" }; 
        }
    }
    if (pnumber[0] == '0' || pnumber[0] == '1') 
        throw std::domain_error { "Invalid Area-Code" };
    if (pnumber[3] == '0' || pnumber[3] == '1') 
        throw std::domain_error { "Invalid Exchange-Code" };
    
    this->_number = std::move(pnumber);
    this->_area = this->_number.substr(0, 3);
    this->_exchange = this->_number.substr(3, 3);
    this->_subscriber = this->_number.substr(6);
    
    // Build formatted string efficiently
    this->_formatted.reserve(14); // "(xxx) xxx-xxxx" = 14 characters
    this->_formatted = '(' + this->_area + ") " + this->_exchange + '-' + this->_subscriber;
}

string phone_number::phone_number::number() const { return _number; }

string phone_number::phone_number::area_code() const { return _area; }

string phone_number::phone_number::exchange() const { return _exchange; }

string phone_number::phone_number::subscriber() const { return _subscriber; }

phone_number::phone_number::operator string() const { return _formatted; }