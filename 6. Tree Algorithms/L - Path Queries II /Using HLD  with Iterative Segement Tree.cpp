#include <bits/stdc++.h>
using namespace std;
static const int INF64 = 1e9;
static const int NEG_INF64 = -1e9;
struct Node {
    int mx;
    Node() {}
    Node(int n) : mx(n) {} // same as make leaf node
};
Node make_identity() {
    return Node{NEG_INF64};
}
Node make_leaf(int v) {
    return Node{v};
}
Node merge_node(const Node &a, const Node &b){
    Node c;
    c.mx  = max(a.mx, b.mx);
    return c;
}
struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> val;
    vector<int> parent, depth, heavy, sz, head, pos;
    int cur_pos;
    struct SegTree {
        vector<int> A;
        vector<Node> st;
        SegTree() {}
        SegTree(vector<int> A) {
            this->A = A;
            st.assign((A.size()) * 4, make_identity());
            build();
        }
        void build() {
            for (int i = 0; i < A.size(); i++)
                st[i + A.size()] = Node(A[i]);
            for (int i = A.size() - 1; i > 0; i--)
                st[i] = merge_node(st[i << 1], st[i << 1 | 1]);
        }
        Node query(int l, int r) {
            Node res1 = make_identity(), res2 = make_identity();
            for (l += A.size(), r += A.size(); l < r; l >>= 1, r >>= 1) {
                if (l & 1) res1 = merge_node(res1, st[l++]);
                if (r & 1) res2 = merge_node(st[--r], res2);
            }
            return merge_node(res1, res2);
        }
        void update(int p, int v) {
            for (st[p += A.size()] = make_leaf(v); p > 1; p >>= 1)
                st[p >> 1] = merge_node(st[(p | 1) ^ 1], st[p | 1]);
        }
    };
    SegTree seg;
    HLD(int n = 0){ init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n+1, {});
        val.assign(n+1, 0);
        parent.assign(n+1, -1);
        depth.assign(n+1, 0);
        heavy.assign(n+1, -1);
        sz.assign(n+1, 0);
        head.assign(n+1, 0);
        pos.assign(n+1, 0);
        cur_pos = 1;
    }
    void addEdge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    void setValue(int u, int x) { val[u] = x; }
    int dfs_sz(int u, int p){
        parent[u] = p;
        depth[u] = (p == -1 ? 0 : depth[p] + 1);
        sz[u] = 1;
        heavy[u] = -1;
        int best = 0;
        for (int v : g[u]) {
            if (v != p) {
                int sub = dfs_sz(v, u);
                sz[u] += sub;
                if (sub > best) {
                    best = sub;
                    heavy[u] = v;
                }
            }
        }
        return sz[u];
    }
    void dfs_hld(int u, int h){
        head[u] = h;
        pos[u] = cur_pos++;
        if (heavy[u] != -1) {
            dfs_hld(heavy[u], h);
        }
        for (int v : g[u]) {
            if (v != parent[u] && v != heavy[u]) {
                dfs_hld(v, v);
            }
        }
    }
    void build(int root = 1){
        dfs_sz(root, -1);
        dfs_hld(root, root);
        vector<int> base(n + 2, 0);
        for (int u = 1; u <= n; ++u) {
            base[pos[u]] = val[u];
        }
        seg = SegTree(base);
    }
    void pointSet(int u, int x) {
        val[u] = x;
        seg.update(pos[u], x);
    }
    Node queryPath(int u, int v) {
        Node res = make_identity();
        while(head[u] != head[v]){
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }
            Node cur = seg.query(pos[head[u]], pos[u] + 1);
            res = merge_node(res, cur);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        Node last = seg.query(pos[u], pos[v] + 1);
        res = merge_node(res, last);
        return res;
    }
    Node SegmentQuery(int l, int r) { return seg.query(l, r); }
    Node SubtreeQuery(int u) { return seg.query(pos[u], pos[u] + sz[u] - 1); }
    int PathQuery(int u, int v) { return queryPath(u, v).mx; }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    HLD h(N);
    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        h.setValue(i, x);
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        h.addEdge(a, b);
    }
    h.build(1);
    while(Q--){
        int t; cin>>t;
        if (t == 1) {
            int u;
            int x;
            cin >> u >> x;
            h.pointSet(u, x);
        } else {
            int u, v;
            cin >> u >> v;
            cout << h.PathQuery(u, v) << " ";
        }
    }
    return 0;
}
