#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	const string& prefix) {
	string val;
	val += prefix;
	auto beg = lower_bound(range_begin, range_end, val);
	val += char(255);
	auto end = upper_bound(range_begin, range_end, val);
	return { beg, end };
}
/*template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	char prefix) {

	string val;
	val += prefix;
	auto beg = find_if(range_begin, range_end,
		[&prefix](const string& s) {
			return s[0] == prefix;
		});
	auto end = upper_bound(beg, range_end, val,
		[](const string& elem, const string& value) {
			return elem[0] == value[0];
		});
	return { beg, end };
}*/

int main() {
	//vector<string> v{ "c", "ca", "cz", "cw"};
	//auto p = minmax_element(v.begin(), v.end());
	//cout << *p.first << "~~~" << *p.second<<endl;

	//return 0;
	const vector<string> sorted_strings = { "moscow", "murmansk", "vologda" };

	const auto m_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "m");
	for (auto it = m_result.first; it != m_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto p_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "p");
	cout << (p_result.first - begin(sorted_strings)) << " " <<
		(p_result.second - begin(sorted_strings)) << endl;

	const auto z_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "z");
	cout << (z_result.first - begin(sorted_strings)) << " " <<
		(z_result.second - begin(sorted_strings)) << endl;

	return 0;
}
