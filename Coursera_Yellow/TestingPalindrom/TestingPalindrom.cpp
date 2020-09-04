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

bool IsPalindrom(const string& str) {
    string s;
    for (const auto& ch : str) {
        s = ch + s;
    }
    return s == str;
}

void t1() {
    Assert(IsPalindrom(""), "empty string");
}
void t2() {
    Assert(IsPalindrom("a"), "one symbol");
}
void t3() {
    Assert(IsPalindrom("aa"), "two symbols");
}
void t4() {
    Assert(IsPalindrom("a a"), "");
}
void t5() {
    Assert(IsPalindrom(" a "), "");
}
void t6() {
    Assert(IsPalindrom(" aa "), "");
}
void t7() {
    Assert(!IsPalindrom("aa a"), "");
}
void t8() {
    Assert(IsPalindrom("abcdedcba"), "");
}
void t9() {
    Assert(!IsPalindrom("abcdeqcba"), "");
}
void t10() {
    Assert(!IsPalindrom("qbcdedcba"), "");
}
void t11() {
    Assert(!IsPalindrom("abcqwecba"), "");
}

void CommonTest() {
    Assert(IsPalindrom(""), "Is  palindrome");
    Assert(IsPalindrom(" "), "Is  palindrome");
    Assert(IsPalindrom("lool"), "Is  palindrome");
    Assert(IsPalindrom("o"), "Is  palindrome");
    Assert(IsPalindrom("1"), "Is  palindrome");
    Assert(!IsPalindrom("madaM"), "Not a palindrome");
    Assert(!IsPalindrom("leveL"), "Not a palindrome");
    Assert(!IsPalindrom("Level"), "Not a palindrome");
    Assert(!IsPalindrom("level "), "Not a palindrome");
    Assert(!IsPalindrom(" llevell"), "Not a palindrome");
    Assert(IsPalindrom("top pot"), " is palindrome");
    Assert(IsPalindrom("l e v e l"), "Is palindrome");
    Assert(IsPalindrom("l  e  v  e  l"), "Is palindrome");
    Assert(!IsPalindrom(" lev e  l   "), "Is not palindrome");
    Assert(!IsPalindrom("mada m"), "Is not palindrome");
    Assert(!IsPalindrom("   madam  "), "Is not palindrome");
    Assert(IsPalindrom("MADAM"), "Is  palindrome");
    Assert(IsPalindrom("o lol o"), "Is  palindrome");
    Assert(!IsPalindrom(" madam"), "Is not palindrome");
    Assert(!IsPalindrom(" madrydam"), "Is not palindrome");
    Assert(IsPalindrom("wasitacaroracatisaw"), "Is  palindrome");
    Assert(IsPalindrom("   tutneotmfmtoentut   "), "Is  palindrome");
    Assert(!IsPalindrom("  lol   "), "noIs  palindrome");
    Assert(!IsPalindrom(" lol   "), "Is no palindrome");
    Assert(!IsPalindrom("lol   "), "Is  no palindrome");
    Assert(!IsPalindrom("   lol  "), "Is no palindrome");
    Assert(!IsPalindrom("   lol "), "Is no palindrome");
    Assert(!IsPalindrom("   lol"), "Is no palindrome");
    Assert(!IsPalindrom("  lol "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("ldfol "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("lovfdvl "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("lo vf  l "), "Is no palindrome");
    Assert(!IsPalindrom("       lol "), "Is no palindrome");
    Assert(!IsPalindrom("         lol "), "Is no palindrome");
    Assert(!IsPalindrom("  ldcsol "), "Is no palindrome");
    Assert(!IsPalindrom(" logbtl "), "Is no palindrome");
    Assert(!IsPalindrom("lvkkol "), "Is no palindrome");
    Assert(!IsPalindrom("l   ol "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("l   o l "), "Is no palindrome");
    Assert(!IsPalindrom("lcccco     l "), "Is no palindrome");
    Assert(!IsPalindrom("c   lcccocl "), "Is no palindrome");
    Assert(IsPalindrom("              "), "Is palindrome");
    Assert(!IsPalindrom("dddlddocccl "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
    Assert(!IsPalindrom("lol "), "Is no palindrome");
}

int main() {
    TestRunner runner;
    runner.RunTest(CommonTest, "Common Tests");
    runner.RunTest(t1, "1");
    runner.RunTest(t2, "2");
    runner.RunTest(t3, "3");
    runner.RunTest(t4, "4");
    runner.RunTest(t5, "5");
    runner.RunTest(t6, "6");
    runner.RunTest(t7, "7");
    runner.RunTest(t8, "8");
    runner.RunTest(t9, "9");
    runner.RunTest(t10,"10");
    runner.RunTest(t11,"11");
    return 0;
}
