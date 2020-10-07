#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include "date.h"

class Database {
public:
    void Add(const Date &date, const std::string &event);

    template<typename Predicate>
    int RemoveIf(Predicate pred) {
        int res = 0;
        for (auto p = storage.begin(); p != storage.end();) {
            auto &date = p->first;
            auto &events = p->second;
            auto it = std::stable_partition(events.begin(), events.end(), [pred, date](const std::string &s) {
                return !pred(date, s);
            });
            res += std::distance(it, events.end());
            auto temp = it;
            while (temp != events.end()) {
                set_storage[date].erase(*(temp++));
            }
            events.erase(it, events.end());


            if (events.empty()) {
                storage.erase(p++);
                set_storage.erase(date);
            } else {
                ++p;
            }
        }
        return res;
    }

    template<typename Predicate>
    std::vector<std::pair<Date, std::string>> FindIf(Predicate pred) const {
        std::vector<std::pair<Date, std::string>> res;
        for (const auto &p: storage) {
            const auto &date = p.first;
            const auto &events = p.second;
            auto lamb = [pred, date](const std::string &s) {
                return pred(date, s);
            };
            for (auto it = std::find_if(events.begin(), events.end(), lamb);
                 it != events.end();
                 it = std::find_if(it + 1, events.end(), lamb)) {
                res.push_back({date, *it});
            }
        }
        return res;
    }

    [[nodiscard]] std::pair<Date, std::string> Last(const Date &d) const;

    void Print(std::ostream &out) const;

    friend void TestAdd();


private:
    std::map<Date, std::vector<std::string>> storage;
    std::map<Date, std::set<std::string>> set_storage;
};

void TestAdd();
