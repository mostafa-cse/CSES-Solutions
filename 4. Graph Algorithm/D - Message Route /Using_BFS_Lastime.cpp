#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> adj[100005];
int32_t main() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	queue<int> q;
	vector<int> parent(n + 1, -1);


	q.push(1);
	parent[1] = 0;
	while(!q.empty()) {
		const auto u = q.front();
		q.pop();

		for (int v : adj[u]) {
			if (parent[v] == -1) {
				parent[v] = u;
				q.push(v);
			}
		}

	}

	if (parent[n] != -1) {
		vector<int> ans;
		function<void(int)> print = [&](int u) -> void {
			if (u == 0) return;
			print(parent[u]);
			ans.push_back(u);
		};
		print(n);

		cout << ans.size() << endl;
		for (int i : ans) {
			cout << i << " ";
		}
		cout << endl;
	} else {
		cout << "IMPOSSIBLE" << endl;
	}
	return 0;
}
