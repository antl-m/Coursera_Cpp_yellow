#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename T> T Sqr(const T& x);
template <typename T> vector<T> Sqr(vector<T> vec);
template <typename F, typename S> pair<F, S> Sqr(pair<F, S> p);
template <typename K, typename V> map<K, V> Sqr(map<K, V> m);


template <typename T>
T Sqr(const T& x) {
	return x * x;
}

template <typename T>
vector<T> Sqr(vector<T> vec) {
	for (auto& it: vec) {
		it = Sqr(it);
	}
	return vec;
}

template <typename F, typename S>
pair<F, S> Sqr(pair<F, S> p) {
	p.first = Sqr(p.first);
	p.second = Sqr(p.second);
	return p;
}

template <typename K, typename V>
map<K, V> Sqr(map<K, V> m) {
	for (auto& [key, value] : m) {
		value = Sqr(value);
	}
	return m;
}

int main()
{
	// Пример вызова функции
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}