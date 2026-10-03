#include <bits/stdc++.h>
#define int long long
using namespace std;
struct SegmentTree {
    vector<int> sgt;
    vector<int> a;
    int n;
    SegmentTree() {}
    SegmentTree(int N) {
        this->n = N;
        a.assign(n + 1, 0);
        sgt.assign((n + 1) * 4 + 1, 0);
    }
    int combine(int a, int b) {
        return a + b;        // ➜ sum
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            sgt[node] = value;
            return;
        }
        int mid = l + (r - l) / 2;
        if(idx <= mid) {
            update(node * 2, l, mid, idx, value);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, value);
        }
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return 0; // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void build() { build(1, 1, n); }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};

struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> val;
    vector<int> parent, depth, heavy, sz, head, pos;
    int cur_pos;
    SegmentTree st;
    HLD(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n + 1, {});
        val.assign(n + 1, 0);
        parent.assign(n + 1, -1);
        depth.assign(n + 1, 0);
        heavy.assign(n + 1, -1);
        sz.assign(n + 1, 0);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        cur_pos = 1;
        st = SegmentTree(n);
    }

    void addEdge(int u, int v) {
        g[u].push_back(v), g[v].push_back(u);
    }
    void setValue(int u, int x) {
        val[u] = x;
    }
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
        vector<int> base(n + 1, 0);
        for (int u = 1; u <= n; ++u) {
            base[pos[u]] = val[u];
        }
        st.a = base;
        st.build();
    }
    void pointSet(int u, int x) {
        val[u] = x;
        st.update(pos[u], x);
    }
    int querySegment(int l, int r) {
        return st.query(l, r);
    }
    int querySubtree(int u) {
        return st.query(pos[u], pos[u] + sz[u] - 1);
    }
    int queryPath(int u, int v) {
        int res = 0;
        while(head[u] != head[v]){
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }
            int cur = st.query(pos[head[u]], pos[u]);
            res += cur;
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        int last = st.query(pos[u], pos[v]);
        res += last;
        return res;
    }
    int querySubtreeSum(int u) { return querySubtree(u); };
    int queryPathSum(int u, int v) { return queryPath(u, v); }
};

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
            int u;
            cin >> u;
            cout << h.queryPathSum(1, u) << "\n";
        }
    }
    return 0;
}
