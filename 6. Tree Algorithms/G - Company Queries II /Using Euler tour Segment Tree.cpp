#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
struct Node {
    int depth, node;
    Node(int depth = 1e12, int node = 1e12) : node(node), depth(depth) {}
};
struct SegmentTree {
    vector<Node> sgt;
    vector<Node> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.resize(n + 1, 0);
        sgt.resize((n + 1) * 4 + 1);
    }
    Node combine(Node a, Node b) {
        if (a.depth < b.depth) return a;
        return b;
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = Node(a[l]);
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    Node query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return Node(); // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void build() { build(1, 1, n); }
    int query(int l, int r) { return query(1, 1, n, l, r).node; }
};
const int M = 2e5;
vector<int> adj[M + 1], depth(M + 1), pos(M + 1);
vector<Node> tour;
void dfs(int u) {
    tour.emplace_back(depth[u], u);
    for (int v : adj[u]) {
        depth[v] = depth[u] + 1;
        dfs(v);
        tour.emplace_back(depth[u], u); // always create a bug
    }
}
signed main() {
    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;

        adj[p].push_back(i);
    }

    tour.push_back(0);
    dfs(1);
    vector<int> position(n + 1, -1);
    for (int i = 1; i < tour.size(); i++) {
        int node = tour[i].node;
        if (position[node] < 0) {
            position[node] = i;
        }
    }
    dout(position);
    
    SegmentTree tree(tour.size());
    tree.a = tour;
    tree.build();

    while (q--) {
        int a, b;
        cin >> a >> b;

        a = position[a];
        b = position[b];
        if (a > b) {
            swap(a, b);
        }
        cout << tree.query(a, b) << endl;
    }
    return 0;
}
