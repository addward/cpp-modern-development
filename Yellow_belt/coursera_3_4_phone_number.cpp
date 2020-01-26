#include <string>
#include <sstream>
#include "phone_number.h"

using namespace std;

void readPart(stringstream& ss,string& str, char delim){
    getline(ss, str, delim);
}

PhoneNumber::PhoneNumber(const string& international_number){
    stringstream ss(international_number);
    if (ss.peek() != '+'){
        throw invalid_argument("No + before the number");
    }
    ss.ignore(1);
    string city_code, country_code, local_number;
    readPart(ss, country_code, '-');
    readPart(ss, city_code, '-');
    ss >> local_number;

    if (city_code.empty() || country_code.empty() || local_number.empty()){
        throw invalid_argument("invalid number");
    }

    PhoneNumber::city_code_ = city_code;
    PhoneNumber::country_code_ = country_code;
    PhoneNumber::local_number_ = local_number;
}

string PhoneNumber::GetCityCode() const {
    return PhoneNumber::city_code_;
}

string PhoneNumber::GetCountryCode() const {
    return PhoneNumber::country_code_;
}

string PhoneNumber::GetInternationalNumber() const {
    return ('+' + PhoneNumber::country_code_ + '-' + PhoneNumber::city_code_ + '-' + PhoneNumber::local_number_);
}

string PhoneNumber::GetLocalNumber() const {
    return PhoneNumber::local_number_;
}

/*
#include <stdexcept>
#include <string>
#include <sstream>
#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream is(international_number);

  char sign = is.get();
  getline(is, country_code_, '-');
  getline(is, city_code_, '-');
  getline(is, local_number_);

  if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
  }
}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

string PhoneNumber::GetCityCode() const {
  return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
  return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
*/
