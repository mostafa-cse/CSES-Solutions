#include<bits/stdc++.h>
using namespace std;
 
int n, m, par[100005];
vector<int> a[100005], trace;
int d[100005];
 
void dfs(int u) {
    for(int v : a[u]) {
        if(v != par[u]) {
            par[v] = u;
            dfs(v);
        }
    }
}
 
int find(int u) {
    if(d[u] < 0) return u;
    d[u] = find(d[u]);
    return d[u];
}
 
bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return false;
    if(d[u] < d[v]) swap(u, v);
    d[v] += d[u];
    d[u] = v;
    return true;
}
 
main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    memset(d, -1, sizeof(d));
    for(int i = 1; i <= m; ++i) {
        int u,v;cin >> u >> v;
        if(!merge(u, v)) {
            dfs(u);
            int u = v;
            while(u != 0) {
                trace.push_back(u);
                u = par[u];
            }
            trace.push_back(v);
            cout << trace.size() << "\n";
            for(int i : trace) cout << i << " ";
            return 0;
        } else {
            a[u].push_back(v);
            a[v].push_back(u);
        }
    }
    cout << "IMPOSSIBLE";
}