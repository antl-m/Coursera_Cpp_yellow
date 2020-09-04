#include <iostream>
#include <string>
#include <map>
//#include <pair>
#include <tuple>
#include <vector>

using namespace std;

//enum class Lang {
//    DE, FR, IT
//};
//
//struct Region {
//    string std_name;
//    string parent_std_name;
//    map<Lang, string> names;
//    int64_t population;
//};

bool operator<(const Region& lhs, const Region& rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
        tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& base) {
    map<Region, int> out;
    for (const Region& reg : base) {
        if (out.count(reg) == 0) {
            out[reg] = 1;
        } else {
            ++out[reg];
        }
    }
    int max = 0;
    for (const auto& [key, val] : out) {
        if (val > max)
            max = val;
    }
    return max;
}

//int main()
//{
//    return 0;
//}