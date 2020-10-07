#include "date.h"

Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
        throw std::logic_error("Month value is invalid: " + std::to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
        throw std::logic_error("Day value is invalid: " + std::to_string(new_day));
    }
    day = new_day;
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

bool operator<(const Date &lhs, const Date &rhs) {
    /// воспользуемся тем фактом, что векторы уже можно сравнивать на <:
    /// создадим вектор из года, месяца и дня для каждой даты и сравним их
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
           std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

std::ostream &operator<<(std::ostream &stream, const Date &date) {
    stream << std::setw(4) << std::setfill('0') << date.GetYear() <<
           "-" << std::setw(2) << std::setfill('0') << date.GetMonth() <<
           "-" << std::setw(2) << std::setfill('0') << date.GetDay();
    return stream;
}

Date ParseDate(std::istream &in) {
    bool ok = true;

    int year;
    ok = static_cast<bool>(in >> year);
    ok = ok && (in.peek() == '-');
    in.ignore(1);

    int month;
    ok = ok && (in >> month);
    ok = ok && (in.peek() == '-');
    in.ignore(1);

    int day;
    ok = ok && (in >> day);

    if (!ok) {
        throw std::logic_error("Wrong date format");
    }
    return Date(year, month, day);
}

bool operator==(const Date &lhs, const Date &rhs) {
    return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
           std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date &lhs, const Date &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return !(lhs < rhs);
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return !(lhs == rhs);
}
