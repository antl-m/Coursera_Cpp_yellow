#include <iostream>
#include <map>
#include <exception>

using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& m, const K& k) {
	if(m.count(k) == 0)
		throw runtime_error("Not found");
	return m[k];
}

//int main()
//{
//	return 0;
//}