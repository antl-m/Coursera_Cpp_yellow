#include <iostream>
#include <sstream>
#include <exception>
#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
	istringstream in(international_number);

	if (in.eof() || in.get() != '+')
		throw invalid_argument("Invalid argument");
	
	getline(in, country_code_, '-');
	
	if(in.eof() || country_code_.empty())
		throw invalid_argument("Invalid argument");

	getline(in, city_code_, '-');

	if(in.eof() || city_code_.empty())
		throw invalid_argument("Invalid argument");

	getline(in, local_number_);

	if (local_number_.empty())
		throw invalid_argument("Invalid argument");
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
	return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}

//int main() {
//	PhoneNumber p("+--");
//	cout << p.GetLocalNumber() << endl;
//	cout << p.GetCityCode() << endl;
//	cout << p.GetCountryCode() << endl;
//	cout << p.GetInternationalNumber() << endl;
//	return 0;
//}