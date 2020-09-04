#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
	sort(elements.begin(), elements.end());
	auto it = unique(elements.begin(), elements.end());
	elements.erase(it, elements.end());
}

int main()
{
	int N;
	cin >> N;
	vector<int> v;
	for (int i = N; i > 0; v.push_back(i--));
	do {
		for (auto i : v)
			cout << i << ' ';
		cout << endl;
	} while (prev_permutation(v.begin(), v.end()));

	return 0;
}
