#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(
	const set<int>& numbers,
	int border) {

	if (numbers.size() == 0)
		return numbers.end();

	auto t = numbers.equal_range(border);

	if (t.second == t.first) {
		if (t.first == numbers.end())
			return prev(t.first);
		else if (t.first == numbers.begin())
			return t.first;
		else if (abs(border - *prev(t.first)) <= abs(border - *t.second))
			return prev(t.first);
		else
			return t.first;
	}
	else
		return t.first;
}

int main()
{
	set<int> n{ 1,4,6 };
	cout << *FindNearestElement(n, 100);
	return 0;
}
