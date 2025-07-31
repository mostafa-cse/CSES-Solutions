#include <bits/stdc++.h>
#define int long long
using namespace std;
#define INF 1e18

vector<vector<int>> capacity, adj;
int n;
int bfs(int s, int t, vector<int> &parent) {
	fill(parent.begin(), parent.end(), -1);
	parent[s] = -2;

	queue<pair<int, int>> q;
	q.push({s, INF});
	
	while (!q.empty()) {
		const auto [cur, flow] = q.front();
		q.pop();
		for (int next : adj[cur]) {
			if (parent[next] == -1 and capacity[cur][next] > 0) {
				parent[next] = cur;
				int _nflow = min(flow, capacity[cur][next]);
				if (next == t) {
					return _nflow;
				}
				q.push({next, _nflow});
			}
		}
	}
	return 0;
}
int maxFlow(int s, int t) {
	int flow = 0;
	vector<int> parent(n + 1);
	int _nflow;
	while (_nflow = bfs(s, t, parent)) {
		flow += _nflow;
		int cur = t;
		while (cur != s) {
			int prev = parent[cur];
			capacity[prev][cur] -= _nflow;
			capacity[cur][prev] += _nflow;
			cur = prev;
		}
	}
	return flow;
}
int32_t main(int32_t argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
	int m;
	cin >> n >> m;

	capacity= vector<vector<int>> (n + 1, vector<int>(n + 1, 0));
	adj = vector<vector<int>> (n + 1);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(v);
		adj[v].push_back(u);
		capacity[u][v] += w;
		// capacity[v][u] = 0;
	}
	cout << maxFlow(1, n) << endl;
	return 0;
}