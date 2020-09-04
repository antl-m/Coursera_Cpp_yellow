#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	cerr << "Error";
	cout << "Success";

	return 0;
	/*int64_t N;
	int64_t avg = 0;
	cin >> N;
	vector<int64_t> temps(N, 0);
	for (int64_t& it : temps) {
		cin >> it;
		avg += it;
	}
	avg /= N;

	vector<int64_t> out;
	for (int64_t i = 0; i < N; ++i) {
		if (temps[i] > avg)
			out.push_back(i);
	}
	cout << out.size() << endl;
	bool first = true;
	for (const int64_t& it: out) {
		if (first) 
			first = false;
		else
			cout << " ";
		cout << it;
	}
	return 0;
	*/
}