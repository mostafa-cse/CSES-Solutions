#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<set<int>> dp(n);
	vector<int> ans(n);

	function<void(int, int)> dfs = [&](int u, int p) -> void {
		dp[u].insert(a[u]);
		for (int v : adj[u]) {
			if (v != p) {
				dfs(v, u);
				if (dp[v].size() > dp[u].size()) {
					swap(dp[u], dp[v]);
				}

				// efficient merging to root 
				for (int color : dp[v]) {
					dp[u].insert(color);
				}
			}
		}
		ans[u] = dp[u].size();
	};
	dfs(0, -1);
	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
	}
	return 0;
}
