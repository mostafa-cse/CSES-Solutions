#include<bits/stdc++.h>
#define int long long
using namespace std;
#define sz(a) (int)x.size()
string cdn[2] = {"YES", "NO"};
#define all(x) x.begin(), x.end()
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
vector<int> eularWalk(vector<vector<pair<int, int>>>&g, int nedges, int src = 0) {
    int n = g.size();
    vector<int> D(n, 0),its(n, 0), eu(nedges), ret, s = {src};
    D[src]++;
    while (!s.empty()) {
        int x = s.back();
        int &it = its[x];
        int end = g[x].size();
        if (it == end) {
            ret.push_back(x);
            s.pop_back();
            continue;
        }

        auto[y, e] = g[x][it++];
        if (eu[e] == 0) {
            D[x]--, D[y]++;
            eu[e] = 1;
            s.push_back(y);
        }
    }
    for (int x : D) {
        if (x < 0 or ret.size() != nedges + 1) return {};
    }
    return {ret.rbegin(), ret.rend()};
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n);
    vector<int> in(n, 0), out(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        in[v]++;
        out[u]++;
        g[u].push_back({v, i});
    }
    for (int i = 0; i < n; i++) {
        if (i == 0 or i == n - 1) {
            if (i == 0 and in[i] + 1 != out[i]) {
                return cout << "IMPOSSIBLE" << endl, 0;
            } else if (i == n - 1 and in[n - 1] != out[n - 1] + 1) {
                return cout << "IMPOSSIBLE" << endl, 0;
            }
        } else {
            if (in[i] != out[i]) {
                return cout << "IMPOSSIBLE" << endl, 0;
            }
        }
    }

    vector<int> ans = eularWalk(g, m, 0);
    if (ans.empty()) {
        return cout << "IMPOSSIBLE" << endl, 0;
    }
    for (int i : ans) {
        cout << i + 1 << " ";
    }
    return 0;
}
