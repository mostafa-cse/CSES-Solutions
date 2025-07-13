#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
 
using namespace std;
 
inline int Read() {
	int x;
	char a;
	do { a = getchar_unlocked(); } while (!isdigit(a));
	x = a - '0';
	for (a = getchar_unlocked(); isdigit(a); a = getchar_unlocked())
		x = 10 * x + a - '0';
	return x;
}
 
inline void Print(int x) {
	if (x <= 9)
		putchar_unlocked('0' + x);
	else {
		Print(x / 10);
		putchar_unlocked('0' + x % 10);
	}
}
 
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, q, curdepth = 0;
	n = Read(), q = Read();
	vector<vector<int>> g(n + 1);
	vector<int> t(n + 1), depth(n + 1), root(n + 1), rootposition(n + 1), startdepth(n + 1), exitdepth(n + 1), cycleroot(n + 1), cyclesize(n + 1), seen(n + 1), cycle;
	for (int i = 1; i <= n; ++i) {
		t[i] = Read();
		g[t[i]].emplace_back(i);
	}
	function<void(int)> dfs = [&](int node) {
		startdepth[node] = curdepth++;
		for (auto x : g[node])
			if (root[x] != x) {
				depth[x] = depth[node] + 1;
				root[x] = root[node];
				cycleroot[x] = cycleroot[node];
				dfs(x);
			}
		exitdepth[node] = curdepth;
	};
	for (int i = 1; i <= n; ++i) {
		if (root[i])
			continue;
		int cur = i;
		while (!seen[cur]) {
			seen[cur] = 1;
			cur = t[cur];
		}
		while (cycle.empty() || cur != cycle[0]) {
			rootposition[cur] = cycle.size();
			cycle.emplace_back(cur);
			root[cur] = cur;
			cycleroot[cur] = i;
			cur = t[cur];
		}
		for (auto x : cycle)
			curdepth = 0, dfs(x), cyclesize[x] = cycle.size();
		cycle.clear();
	}
	while (q--) {
		int a, b, ans = -1;
		a = Read(), b = Read();
		if (cycleroot[a] == cycleroot[b])
			if (root[b] == b) {
				ans = depth[a];
				a = root[a];
				ans += (rootposition[b] - rootposition[a] + cyclesize[a]) % cyclesize[a];
			}
			else if (root[a] == root[b] && startdepth[b] <= startdepth[a] && startdepth[a] < exitdepth[b])
				ans = depth[a] - depth[b];
        cout << ans << endl;
    }
}
