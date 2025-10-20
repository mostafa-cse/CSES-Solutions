// https://cses.fi/problemset/hack/1139/entry/700222/
#include <bits/stdc++.h>
using namespace std;

vector<int> c;
vector<vector<int>> adj;
vector<int> result;
vector<int> last;

struct union_find {
    union_find(int n = 0): parent(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    void combine(int i, int j) {
        i = find(i);
        j = find(j);
        parent[i] = j;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    vector<int> parent;
};

int tarjan_lca_dfs(vector<int>& ancestor, vector<char>& visited, union_find& u, int root, int parent) {
    int& r = result[root] += 1;
    ancestor[root] = root;
    for (int child: adj[root]) {
        if (child == parent) continue;
        r += tarjan_lca_dfs(ancestor, visited, u, child, root);
        u.combine(u.find(root), u.find(child));
        ancestor[u.find(root)] = root;
    }
    visited[root] = true;
    int i = last[c[root]];
    if (i >= 0 && visited[i]) {
        --result[ancestor[u.find(i)]];
    }
    last[c[root]] = root;
    return r;
}

void tarjan_lca(int root) {
    const int n = adj.size();
    union_find u(n);
    vector<char> visited(n, false);
    vector<int> ancestor(n);
    tarjan_lca_dfs(ancestor, visited, u, root, -1);
}

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;

    c.resize(n);
    adj.resize(n);
    result.resize(n);
    vector<pair<int, int>> cc(n);
    for (int i = 0; i < n; ++i) {
        cin >> cc[i].first;
        cc[i].second = i;
    }
    sort(cc.begin(), cc.end());
    int color_cnt = 1;
    c[cc[0].second] = color_cnt;
    for (int i = 1; i < n; ++i) {
        if (cc[i].first != cc[i - 1].first) ++color_cnt;
        c[cc[i].second] = color_cnt;
    }
    last.resize(color_cnt + 1, -1);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    tarjan_lca(0);
    for (int i: result) cout << i << " ";
    cout << "\n";
}
