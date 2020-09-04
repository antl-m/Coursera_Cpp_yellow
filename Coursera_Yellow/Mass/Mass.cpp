#include <iostream>

using namespace std;

int main() {

	uint64_t N, R, W, H, D, sum{ 0 };
	cin >> N >> R;
	for (uint64_t i = 0; i < N; ++i) {
		cin >> W >> H >> D;
		sum += W * H * D * R;
	}
	cout << sum;
	return 0;
}