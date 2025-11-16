#include "phone_number.h"

#include <stdexcept>
#include <regex>

using std::string;

phone_number::phone_number::phone_number(const string &number) {
    string pnumber;
    pnumber.reserve(number.size());
    for (char c : number) {
        if (c >= '0' && c <= '9') {
            pnumber += c;
        }
    }

    size_t plength = pnumber.length();
    if (plength < 10) throw std::domain_error("Less than 10 digits");
    if (plength > 11) throw std::domain_error("More than 11 digits");
    if (plength == 11) {
        if (pnumber[0] == '1') {
            pnumber.erase(0, 1);
        } else {
            throw std::domain_error("Should start with 1");
        }
    }

    if (pnumber[0] == '0' || pnumber[0] == '1') 
        throw std::domain_error("Invalid Area-Code");
    if (pnumber[3] == '0' || pnumber[3] == '1') 
        throw std::domain_error("Invalid Exchange-Code");

    _area = pnumber.substr(0, 3);
    _exchange = pnumber.substr(3, 3);
    _subscriber = pnumber.substr(6);
    _number = std::move(pnumber);
    _formatted = "(" + _area + ") " + _exchange + "-" + _subscriber;
}

string phone_number::phone_number::number() const { return _number; }

string phone_number::phone_number::area_code() const { return _area; }

string phone_number::phone_number::exchange() const { return _exchange; }

string phone_number::phone_number::subscriber() const { return _subscriber; }

phone_number::phone_number::operator string() const { return _formatted; }