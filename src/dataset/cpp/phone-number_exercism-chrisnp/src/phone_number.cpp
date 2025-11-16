#include "phone_number.h"

#include <stdexcept>
#include <regex>

using std::string;

phone_number::phone_number::phone_number(const string &number ) {
    auto pnumber = std::regex_replace(number, std::regex {R"([^0-9])"}, "");
    auto plength = pnumber.length();
    if (plength < 10) throw std::domain_error { "Less than 10 digits" };
    if (plength > 11) throw std::domain_error { "More than 11 digits" };
    if (plength == 11) {
        if (pnumber[0] == '1') { pnumber = pnumber.substr(1); }
        else {  throw std::domain_error { "Should start with 1" }; }
    }
    if (pnumber[0] == '0' || pnumber[0] == '1') 
        throw std::domain_error { "Invalid Area-Code" };
    if (pnumber[3] == '0' || pnumber[3] == '1') 
        throw std::domain_error { "Invalid Exchange-Code" };
    this->_area = pnumber.substr(0, 3);
    this->_exchange = pnumber.substr(3, 3);
    this->_subscriber = pnumber.substr(6);
    this->_number = pnumber;
    this->_formatted = "(" + 
                       this->_area + 
                       ") " + 
                       this->_exchange + 
                       "-" + 
                       this->_subscriber;
}

string phone_number::phone_number::number() const { return _number; }

string phone_number::phone_number::area_code() const { return _area; }

string phone_number::phone_number::exchange() const { return _exchange; }

string phone_number::phone_number::subscriber() const { return _subscriber; }

phone_number::phone_number::operator string() const { return _formatted; }
