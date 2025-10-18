#include <bits/stdc++.h>
#define int long long
using namespace std;
struct HLD {
	struct node {
		int depth, jump, par;
	};
	vector<node> info;
	HLD(const vector<vector<int>>& adj, int root) :
		info(adj.size()) {
		dfs(root, root, adj);
	}
	void dfs(int node, int par, const vector<vector<int>>& adj) {
		int par2 = info[par].jump;
		info[node] = {
			info[par].depth + 1,
			info[par].depth - info[par2].depth == info[par2].depth - info[info[par2].jump].depth ? info[par2].jump : par,
			par
		};
		for (int to : adj[node]) {
			if (to == par) continue;
			dfs(to, node, adj);
		}
	}
	int kthPar(int node, int k) const {
		while(k > 0 && node > 0) {
			if(info[node].depth - k <= info[info[node].jump].depth) {
				k -= info[node].depth - info[info[node].jump].depth;
				node = info[node].jump;
			} else {
				k--;
				node = info[node].par;
			}
		}
        if (node == 0) return -1;
		return node;
	}
	int getLCA(int x, int y) const {
		if (info[x].depth < info[y].depth) {
			swap(x, y);
		}
		x = kthPar(x, info[x].depth - info[y].depth);
		if (x == y) {
			return x;
		}
		while(x != y) {
			if(info[x].jump == info[y].jump) {
				x = info[x].par;
				y = info[y].par;
			} else {
				x = info[x].jump;
				y = info[y].jump;
			}
		}
		return x;
	}
	int distEdges(int x, int y) const {
		return info[x].depth + info[y].depth - 2 * info[getLCA(x, y)].depth;
	}
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<vector<int>>adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    HLD algo(adj, 1);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << algo.distEdges(a, b) << endl;
    }
    return 0;
}
