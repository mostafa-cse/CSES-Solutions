#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long cap;
    int rev;
};

const long long INF = 1LL<<60;
struct Dinic {
    int N;
    vector<vector<Edge>> G;
    vector<int> level, ptr;
    
    Dinic(int n): N(n), G(n), level(n), ptr(n) {}
    
    void addEdge(int u, int v, long long c) {
        G[u].push_back({v, c, (int)G[v].size()});
        G[v].push_back({u, 0, (int)G[u].size()-1});
    }
    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(auto &e : G[u]) {
                if(level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }
    
    long long dfs(int u, int t, long long f) {
        if(u == t) return f;
        for(int &cid = ptr[u]; cid < (int)G[u].size(); ++cid) {
            Edge &e = G[u][cid];
            if(level[e.to] == level[u] + 1 && e.cap > 0) {
                long long pushed = dfs(e.to, t, min(f, e.cap));
                if(pushed > 0) {
                    e.cap -= pushed;
                    G[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while(bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while(long long pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dinic D(n + 1);

    for(int i = 0; i < m; i++){
        int a, b;
        long long c;
        cin >> a >> b >> c;
        D.addEdge(a, b, c);
    }

    cout << D.maxFlow(1, n) << "\n";
    return 0;
}
