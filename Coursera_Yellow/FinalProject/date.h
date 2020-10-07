#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <exception>
#include <vector>

class Date {
public:
    /// конструктор выбрасывает исключение, если его аргументы некорректны
    Date(int new_year, int new_month, int new_day);

    [[nodiscard]] int GetYear() const;

    [[nodiscard]] int GetMonth() const;

    [[nodiscard]] int GetDay() const;

private:
    int year;
    int month;
    int day;
};

/// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date &lhs, const Date &rhs);

bool operator==(const Date &lhs, const Date &rhs);

bool operator!=(const Date &lhs, const Date &rhs);

bool operator<=(const Date &lhs, const Date &rhs);

bool operator>(const Date &lhs, const Date &rhs);

bool operator>=(const Date &lhs, const Date &rhs);


// даты будут по умолчанию выводиться в нужном формате
std::ostream &operator<<(std::ostream &stream, const Date &date);

Date ParseDate(std::istream &in);
