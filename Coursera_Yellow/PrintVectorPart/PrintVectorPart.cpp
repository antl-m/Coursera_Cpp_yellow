#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& list) {

	auto bord = find_if(list.begin(), list.end(), [](const int& n) {
		return n < 0;
		});

	while (bord > list.begin()) {
		--bord;
		cout << *bord << " ";
	}
}

int main()
{
	return 0;
}
