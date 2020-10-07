#include "database.h"
#include "condition_parser.h"
#include "test_runner.h"
//#include "tests.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream &is) {
    string res;
    while(is.peek()==' ')
        is.get();
    getline(is, res, '\n');
    return res;
}

void TestAll();


template<typename T1, typename T2>
ostream &operator<<(ostream &out, std::pair<T1, T2> p);

int main() {
    //TestAll();

    Database db;

    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument &) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

//void TestParseEvent() {
//    {
//        istringstream is("event");
//        ASSERT_EQUAL(ParseEvent(is), "event");
//    }
//    {
//        istringstream is("   sport event ");
//        ASSERT_EQUAL(ParseEvent(is), "sport event ");
//    }
//    {
//        istringstream is("  first event  \n  second event");
//        vector<string> events;
//        events.push_back(ParseEvent(is));
//        events.push_back(ParseEvent(is));
//        auto exp = vector<string>{"first event  ", "second event"};
//        ASSERT_EQUAL(events, exp);
//    }
//}

void TestAll() {
    TestRunner tr;
//    tr.RunTest(TestEmptyNode, "Тест 2 из Coursera");
//    tr.RunTest(TestDbAdd, "Тест 3(1) из Coursera");
//    tr.RunTest(TestDbFind, "Тест 3(2) из Coursera");
//    tr.RunTest(TestDbLast, "Тест 3(3) из Coursera");
//    tr.RunTest(TestDbRemoveIf, "Тест 3(4) из Coursera");
//    tr.RunTest(TestInsertionOrder, "Тест на порядок вывода");
//    tr.RunTest(TestsMyCustom, "Мои тесты");
//    tr.RunTest(TestDatabase, "Тест базы данных с GitHub");

//    RUN_TEST(tr, TestParseEvent);
//    RUN_TEST(tr, TestParseCondition);
//    RUN_TEST(tr, TestAdd);
}

template<typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> p) {
    out << p.first << ' ' << p.second;
    return out;
}
