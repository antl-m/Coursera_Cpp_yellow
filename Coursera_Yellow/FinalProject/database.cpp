#include "database.h"
#include "test_runner.h"
#include <iterator>

void Database::Add(const Date &date, const std::string &event) {
    if(!set_storage[date].count(event)){
        set_storage[date].insert(event);
        storage[date].push_back(event);
    }

//    auto& cur = storage[date];
//    if(std::find(cur.begin(), cur.end(), event)==cur.end()){
//        cur.push_back(event);
//    }
}

void Database::Print(std::ostream& out) const {
    for (const auto& item : storage) {
        for (const std::string& event : item.second) {
            out << item.first << " " << event << std::endl;
        }
    }
}

std::pair<Date, std::string> Database::Last(const Date& d) const {
    auto it = storage.upper_bound(d);
    if(it == storage.begin())
        throw std::invalid_argument("Invalid date");
    --it;
    if(d < it->first)
        throw std::invalid_argument("Invalid date");
    return std::pair<Date, std::string>(it->first, it->second.back());
}

void TestAdd(){
    {
        Database db;
        db.Add({2015, 12, 3},"first add");
        db.Add({2016, 11, 4},"first add");
        db.Add({2015, 12, 3},"first add");
        db.Add({2015, 12, 3},"second add");
        std::map<Date, std::vector<std::string>> expected = {
                {{2015, 12, 3}, {"first add", "second add"}},
                {{2016, 11, 4},{"first add"}}
        };
        ASSERT_EQUAL(db.storage, expected);
    }
}