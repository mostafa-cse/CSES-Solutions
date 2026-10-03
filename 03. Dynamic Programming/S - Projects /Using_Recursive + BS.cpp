#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct project {
	int s, e;
	int x;
	project() : s(0), e(0), x(0) {}
	project(int a, int b, int c) : s(a), e(b), x(c){};
	bool operator<(const project &other) const {
		return s < other.s;
	}
}a[200005];
int dp[200005];
int rec(int i) {
	if (i >= n) return 0;
	if (dp[i] != -1) return dp[i];

	int skip = rec(i + 1);
	
	int next_start = a[i].e + 1;
	int next_idx = lower_bound(a,a + n, project(next_start, 0, 0), [](const project &p, const project &q) {
		return p.s < q.s;
	}) - a;
	int take = a[i].x + rec(next_idx);
	return dp[i] = max(skip, take);
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> a[i].s >> a[i].e >> a[i].x;
	}
	sort(a, a + n);
	memset(dp, -1, sizeof dp);
	cout << rec(0) << endl;
	return 0;
}