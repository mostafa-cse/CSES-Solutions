#include <bits/stdc++.h>
#define int long long
#define maxn 200000
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
int n, m = 0, q;
int A[maxn + 10], P[maxn * 5 + 10], ANS[maxn + 10], TREE[maxn * 5 + 10];
struct node {
	int id, p, opt;
};
vector<node> QUE[maxn + 10];
int lowbit(int x) {
	return x & (-x);
}
void modify(int id, int x) {
	for (int i = id; i <= m; i += lowbit(i)) {
		TREE[i] += x;
	}
}
int query(int id) {
	int res = 0;
	for (int i = id; i > 0; i -= lowbit(i)) {
		res += TREE[i];
	}
	return res;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		P[++m] = A[i];
	}

	for (int i = 1; i <= q; i++)
	{
		int l, r, a, b;
		cin >> l >> r >> a >> b;
		P[++m] = a;
		P[++m] = b;
		P[++m] = a - 1;
		P[++m] = b - 1;

		QUE[r].push_back(node{i, b, 1});
		QUE[l - 1].push_back(node{i, b, -1});

		QUE[r].push_back(node{i, a - 1, -1});
		QUE[l - 1].push_back(node{i, a - 1, 1});
	}

	sort(P + 1, P + m + 1);
	m = unique(P + 1, P + m + 1) - P - 1;

	for (int i = 1; i <= n; i++) {
		A[i] = lower_bound(P + 1, P + m + 1, A[i]) - P;
		for (int j = 0; j < QUE[i].size(); j++) { // n >= [l<= i <= r]
			QUE[i][j].p = lower_bound(P + 1, P + m + 1, QUE[i][j].p) - P;
		}
	}
	for (int i = 1; i <= n; i++) {
		modify(A[i], 1);
		for (int j = 0; j < QUE[i].size(); j++) {
			ANS[QUE[i][j].id] += QUE[i][j].opt * query(QUE[i][j].p);
		}
	}
	for (int i = 1; i <= q; i++) {
		cout << ANS[i] << "\n";
	}
	return 0;
}
