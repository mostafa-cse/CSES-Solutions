#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5;
const int B = 32;
int sum[N + 5][B];
int Min[N * 2 + 5][B];
signed main() {
	int n, q;
	cin >> n >> q;

	memset(Min, 0x3f, sizeof Min);
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;

		int lg = log2l(x);
		sum[i][lg] = x;
		Min[i + N][lg] = x;
	}

	for (int i = 1; i <= n; i++) {
		for (int b = 0; b < 32; b++) {
			sum[i][b] += sum[i - 1][b];
		}
	}

	function<void(const int *, const int *, int *)> combine = [&](const int *a, const int *b, int *c) -> void {
		for (int i = 0; i < 32; i++) {
			c[i] = min(a[i], b[i]);
		}
	};

	// Build segment tree for range minimum per bucket
	for (int i = N - 1; i >= 1; i--) {
		combine(Min[i * 2], Min[i * 2 + 1], Min[i]);
	}

	function<void(int, int, int*)> qury = [&](int l, int r, int *res) -> void {
		// initialize result array with +inf
		for (int i = 0; i < 32; i++) res[i] = (int)0x3f3f3f3f3f3f3f3f;
		for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) {
				combine(Min[l++], res, res);
			}
			if (~r & 1) {
				combine(Min[r--], res, res);
			}
		}
	};

	vector<int> best(32, 0);
	while (q--) {
		int l, r;
		cin >> l >> r;

		int res[32];
		long long total = 1;
		qury(l, r, res);
		for (int i = 0; i < 32; i++) {
			if (total < (1LL << (i + 1)) && total < res[i]) {
				break;
			}
			total += sum[r][i] - sum[l - 1][i];
		}
		cout << total << '\n';
	}
	return 0;
}
