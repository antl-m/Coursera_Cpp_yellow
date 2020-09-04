#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;
/***************************************************************************
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < 2)
		return;

	vector<typename RandomIt::value_type> temp(range_begin, range_end);
	auto mid = temp.begin() + temp.size() / 2;
	MergeSort(temp.begin(), mid);
	MergeSort(mid, temp.end());
	merge(temp.begin(), mid, mid, temp.end(), range_begin);
}
****************************************************************************/
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < 2)
		return;

	vector<typename RandomIt::value_type> temp(range_begin, range_end), temp2;
	auto mid1 = temp.begin() + temp.size() / 3;
	auto mid2 = mid1 + temp.size() / 3;
	MergeSort(temp.begin(), mid1);
	MergeSort(mid1, mid2);
	MergeSort(mid2, temp.end());
	merge(temp.begin(), mid1, mid1, mid2, back_inserter(temp2));
	merge(temp2.begin(), temp2.end(), mid2, temp.end(), range_begin);
}

int main()
{
	vector<int> n{ 1,3,2,4,3,5,2,6,3};
	MergeSort(n.begin(), n.end());
	for (auto i : n) {
		cout << i << ", ";
	}
	return 0;
}
