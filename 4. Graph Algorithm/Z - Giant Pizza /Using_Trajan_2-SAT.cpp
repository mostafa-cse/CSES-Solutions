#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> adj; 

    vector<int> disc, low, comp, st;
    vector<bool> on_stack;
    int timer = 0, scc_count = 0;

    TwoSAT(int vars) {
        n = vars;
        adj.assign(2 * n, {});
        disc.assign(2 * n, 0);
        low.assign(2 * n, 0);
        comp.assign(2 * n, 0);
        on_stack.assign(2 * n, false);
    }

    int neg(int x) {
        return x ^ 1; 
    }

    void add_clause(int a, bool a_val, int b, bool b_val) {
        int u = 2 * a ^ (!a_val);
        int v = 2 * b ^ (!b_val);
        adj[neg(u)].push_back(v);
        adj[neg(v)].push_back(u);
    }

    void tarjan(int u) {
        disc[u] = low[u] = ++timer;
        st.push_back(u);
        on_stack[u] = true;

        for (int v : adj[u]) {
            if (!disc[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            ++scc_count;
            while (true) {
                int node = st.back();
                st.pop_back();
                on_stack[node] = false;
                comp[node] = scc_count;
                if (node == u) break;
            }
        }
    }

    bool solve(vector<int>& result) {
        for (int i = 0; i < 2 * n; i++) {
            if (!disc[i]) tarjan(i);
        }

        result.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            result[i] = (comp[2 * i] > comp[2 * i + 1]) ? 0 : 1;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m; // n = wishes, m = toppings
    TwoSAT solver(m);

    for (int i = 0; i < n; i++) {
        char s1, s2;
        int a, b;
        cin >> s1 >> a >> s2 >> b;
        bool a_val = (s1 == '+');
        bool b_val = (s2 == '+');
        solver.add_clause(a - 1, a_val, b - 1, b_val);
    }

    vector<int> result;
    if (!solver.solve(result)) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int x : result) cout << (x ? '+' : '-') << ' ';
        cout << '\n';
    }
    return 0;
}