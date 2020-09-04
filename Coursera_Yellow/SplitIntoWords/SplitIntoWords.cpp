#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
	string::const_iterator word_beg = s.begin();
	string::const_iterator  word_end;
	vector<string> res;

	while (true) {
		word_end = find(word_beg, s.end(), ' ');
		res.push_back({ word_beg, word_end });
		if (word_end == s.end())
			return res;
		word_beg = word_end+1;
	}
}

int main()
{
	for (auto w : SplitIntoWords("Hello World my name is john")) {
		cout << w << '+';
	}
	return 0;
}
