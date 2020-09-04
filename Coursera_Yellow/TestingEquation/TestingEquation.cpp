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

int GetDistinctRealRootCount(double a, double b, double c) {
    if (a == 0) {
        return (b == 0 ? 0 : 1);
    }
    else {
        double d = b * b - 4 * a * c;
        if (d > 0)
            return 2;
        else if (d < 0)
            return 0;
        else
            return 1;
    }
}

void a1b1c1() {
    AssertEqual(GetDistinctRealRootCount(1, -3, 2), 2);
    AssertEqual(GetDistinctRealRootCount(-2, 9, -9), 2);
    AssertEqual(GetDistinctRealRootCount(1, 10, 25), 1);
    AssertEqual(GetDistinctRealRootCount(5, 2, 9), 0);
}

void a0b1c1() {
    AssertEqual(GetDistinctRealRootCount(0, -3, 2), 1);
    AssertEqual(GetDistinctRealRootCount(0, -7, -2), 1);
}

void a1b0c1() {
    AssertEqual(GetDistinctRealRootCount(2, 0, 2), 0);
    AssertEqual(GetDistinctRealRootCount(3, 0, -7), 2);
}

void a1b1c0() {
    AssertEqual(GetDistinctRealRootCount(3, -3, 0), 2);
}

void a1b0c0() {
    AssertEqual(GetDistinctRealRootCount(2, 0, 0), 1);
}

void a0b1c0() {
    AssertEqual(GetDistinctRealRootCount(0, -3, 0), 1);
}

void a0b0c1() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 5), 0);
}

int main() {
    TestRunner r;
    r.RunTest(a1b1c1, "a1b1c1");
    r.RunTest(a0b1c1, "a0b1c1");
    r.RunTest(a1b0c1, "a1b0c1");
    r.RunTest(a1b1c0, "a1b1c0");
    r.RunTest(a1b0c0, "a1b0c0");
    r.RunTest(a0b1c0, "a0b1c0");
    r.RunTest(a0b0c1, "a0b0c1");
    return 0;
}
