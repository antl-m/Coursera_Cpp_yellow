#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
	vector<T> res;
	for (auto it = find_if(elements.begin(), elements.end(),
		[border](const T& elem) {
			return elem > border;
		});
		it != elements.end(); ++it) {
		res.push_back(*it);
	}
	return res;
}

int main()
{
	for (auto t : FindGreaterElements({ 1,2,3,4,5,6,7,8,9 }, 9)) {
		cout << t << " ";
	}
	return 0;
}
