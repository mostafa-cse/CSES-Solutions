#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> g, rg; // graph , reverse graph
    vector<int> comp, order, assignment;

    TwoSAT(int vars) {
        n = vars;
        g.assign(2*n, {});
        rg.assign(2*n, {});
    }

    int neg(int x) {
        return x ^ 1;
    }

    void add_clause(int a, bool a_val, int b, bool b_val) {
        // a_val = true means +a, false means -a
        // Encode literal: x -> 2*x, ¬x -> 2*x+1
        int u = 2*a ^ (!a_val);
        int v = 2*b ^ (!b_val);

        g[neg(u)].push_back(v);
        g[neg(v)].push_back(u);

        rg[v].push_back(neg(u));
        rg[u].push_back(neg(v));
    }

    void dfs1(int u, vector<int>& visited) {
        visited[u] = 1;
        for (int v : g[u])
            if (!visited[v]) dfs1(v, visited);
        order.push_back(u);
    }

    void dfs2(int u, int cid) {
        comp[u] = cid;
        for (int v : rg[u])
            if (comp[v] == -1) dfs2(v, cid);
    }

    bool solve() {
        int N = 2*n;
        vector<int> visited(N, 0);
        comp.assign(N, -1);
        order.clear();

        // 1. Order by finish time
        for (int i = 0; i < N; i++)
            if (!visited[i]) dfs1(i, visited);

        // 2. Reverse graph DFS
        int cid = 0;
        for (int i = N-1; i >= 0; i--) {
            int u = order[i];
            if (comp[u] == -1) dfs2(u, cid++);
        }

        // 3. Check for contradiction
        assignment.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;                              // x and ¬x in same SCC
            assignment[i] = comp[2 * i] > comp[2 * i + 1]; // assign based on SCC order
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m; // n wishes, m toppings
    TwoSAT solver(m);

    for (int i = 0; i < n; i++) {
        char signA, signB;
        int a, b;
        cin >> signA >> a >> signB >> b;
        bool a_val = (signA == '+'); 
        bool b_val = (signB == '+');
        solver.add_clause(a-1, a_val, b-1, b_val);
    }

    if (!solver.solve()) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < m; i++) {
            cout << (solver.assignment[i] ? '+' : '-') << ' ';
        }
        cout << "\n";
    }

    return 0;
}