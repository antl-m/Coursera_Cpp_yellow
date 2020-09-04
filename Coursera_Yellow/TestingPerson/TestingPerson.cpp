#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

// ���� ��� ����������, ���������� ������ ������
//string FindNameByYear(const map<int, string>& names, int year) {
//    string name;  // ���������� ��� ����������
//
//    // ���������� ��� ������� �� ����������� ����� �������, �� ���� � ��������������� �������
//    for (const auto& item : names) {
//        // ���� ��������� ��� �� ������ �������, ��������� ���
//        if (item.first <= year) {
//            name = item.second;
//        }
//        else {
//            // ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
//            break;
//        }
//    }
//
//    return name;
//}
//
//class Person {
//public:
//    void ChangeFirstName(int year, const string& first_name) {
//        first_names[year] = first_name;
//    }
//    void ChangeLastName(int year, const string& last_name) {
//        last_names[year] = last_name;
//    }
//    string GetFullName(int year) {
//        // �������� ��� � ������� �� ��������� �� ��� year
//        const string first_name = FindNameByYear(first_names, year);
//        const string last_name = FindNameByYear(last_names, year);
//
//        // ���� � ���, � ������� ����������
//        if (first_name.empty() && last_name.empty()) {
//            return "Incognito";
//
//            // ���� ���������� ������ ���
//        }
//        else if (first_name.empty()) {
//            return last_name + " with unknown first name";
//
//            // ���� ���������� ������ �������
//        }
//        else if (last_name.empty()) {
//            return first_name + " with unknown last name";
//
//            // ���� �������� � ���, � �������
//        }
//        else {
//            return first_name + " " + last_name;
//        }
//    }
//
//private:
//    map<int, string> first_names;
//    map<int, string> last_names;
//};

void AllTest() {
    Person p1;
    AssertEqual(p1.GetFullName(1970), "Incognito", "just created person");
    p1.ChangeFirstName(1970, "Vasya");
    AssertEqual(p1.GetFullName(1975), "Vasya with unknown last name");
    AssertEqual(p1.GetFullName(1965), "Incognito");
    p1.ChangeLastName(1980, "Pupkin");
    AssertEqual(p1.GetFullName(1975), "Vasya with unknown last name");
    AssertEqual(p1.GetFullName(1985), "Vasya Pupkin");
    p1.ChangeLastName(1960, "Petrov");
    AssertEqual(p1.GetFullName(1965), "Petrov with unknown first name");
    AssertEqual(p1.GetFullName(1955), "Incognito");
    AssertEqual(p1.GetFullName(1980), "Vasya Pupkin");
}

int main() {
    TestRunner r;
    r.RunTest(AllTest, "All Tests");
    return 0;
}
