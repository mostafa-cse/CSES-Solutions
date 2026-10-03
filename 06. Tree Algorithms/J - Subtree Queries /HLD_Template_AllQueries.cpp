#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll INF64 = (ll)4e18;
static const ll NEG_INF64 = (ll)-4e18;
static const long long LCM_CAP = (long long)4e18;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
ll gcdll(ll a, ll b){
    if(a < 0) a = -a; if(b < 0) b = -b;
    return gcd(a, b);
}

ll lcm_capped(ll a, ll b){
    if(a == 0 || b == 0) return 0;
    ll g = gcdll(a, b);
    __int128 t = (__int128)(a / g) * (__int128)b;
    if(t > (__int128)LCM_CAP) return LCM_CAP;
    return (long long)t;
}

struct Node {
    ll sum;
    ll mn;
    ll mx;
    ll gc;
    ll lc;
};
Node make_identity()
{
    return Node{0, INF64, NEG_INF64, 0, 1};
}
Node make_leaf(ll v)
{
    return Node{v, v, v, ll(llabs(v)), ll(llabs(v))};
}

Node merge_node(const Node &a, const Node &b){
    Node c;
    c.sum = a.sum + b.sum;
    c.mn  = std::min(a.mn, b.mn);
    c.mx  = std::max(a.mx, b.mx);
    c.gc  = gcdll(a.gc, b.gc);
    c.lc  = lcm_capped(a.lc, b.lc);
    return c;
}

struct HLD {
    int n;
    vector<vector<int>> g;
    vector<ll> val;        
    vector<int> parent, depth, heavy, sz, head, pos;
    int cur_pos;

    // Segment tree inside
    struct SegTree {
        int n{};
        vector<Node> st;
        void init(int n_) { n = n_; st.assign(4*n + 4, make_identity()); }
        void build(const vector<ll> &base, int p, int l, int r){
            if(l == r){ st[p] = make_leaf(base[l]); return; }
            int m = (l + r) >> 1;
            build(base, p<<1, l, m);
            build(base, p<<1|1, m+1, r);
            st[p] = merge_node(st[p<<1], st[p<<1|1]);
        }
        void build(const vector<ll> &base) { init((int)base.size() - 1); build(base, 1, 1, n); }
        void pointSet(int p, int l, int r, int i, ll v){
            if(l == r){ st[p] = make_leaf(v); return; }
            int m = (l + r) >> 1;
            if(i <= m) pointSet(p<<1, l, m, i, v);
            else       pointSet(p<<1|1, m+1, r, i, v);
            st[p] = merge_node(st[p<<1], st[p<<1|1]);
        }
        void pointSet(int i, ll v) { pointSet(1, 1, n, i, v); }
        Node query(int p, int l, int r, int ql, int qr){
            if(qr < l || r < ql) return make_identity();
            if(ql <= l && r <= qr) return st[p];
            int m = (l + r) >> 1;
            Node L = query(p<<1, l, m, ql, qr);
            Node R = query(p<<1|1, m+1, r, ql, qr);
            return merge_node(L, R);
        }
        Node query(int l, int r){ return query(1, 1, n, l, r); }
    } seg;

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
    void setValue(int u, ll x) { val[u] = x; }
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
        vector<ll> base(n + 1, 0);
        for (int u = 1; u <= n; ++u) {
            base[pos[u]] = val[u];
        }
        seg.build(base);
    }

    // point update
    void pointSet(int u, ll x) {
        val[u] = x;
        seg.pointSet(pos[u], x);
    }

    // basic segments
    Node querySegment(int l, int r) { return seg.query(l, r); }

    // subtree query
    Node querySubtree(int u) { return seg.query(pos[u], pos[u] + sz[u] - 1); }

    // path query
    Node queryPath(int u, int v) {
        Node res = make_identity();
        while(head[u] != head[v]){
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }
            Node cur = seg.query(pos[head[u]], pos[u]);
            res = merge_node(res, cur);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        Node last = seg.query(pos[u], pos[v]);
        res = merge_node(res, last);
        return res;
    }

    // Convenience wrappers
    ll querySubtreeSum(int u){ return querySubtree(u).sum; }
    ll querySubtreeMin(int u){ return querySubtree(u).mn; }
    ll querySubtreeMax(int u){ return querySubtree(u).mx; }
    ll querySubtreeGcd(int u){ return querySubtree(u).gc; }
    ll querySubtreeLcm(int u){ return querySubtree(u).lc; }

    ll queryPathSum(int u,int v){ return queryPath(u,v).sum; }
    ll queryPathMin(int u,int v){ return queryPath(u,v).mn; }
    ll queryPathMax(int u,int v){ return queryPath(u,v).mx; }
    ll queryPathGcd(int u,int v){ return queryPath(u,v).gc; }
    ll queryPathLcm(int u,int v){ return queryPath(u,v).lc; }
};

#ifdef HLD_TEMPLATE_TEST_MAIN
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,Q; if(!(cin>>N>>Q)) return 0;
    HLD h(N);
    for(int i=1;i<=N;i++){ ll x; cin>>x; h.setValue(i,x); }
    for(int i=0;i<N-1;i++){ int a,b; cin>>a>>b; h.addEdge(a,b); }
    h.build(1);
    while(Q--){
        int t; cin>>t;
        if(t==1){ int u; ll x; cin>>u>>x; h.pointSet(u,x); }
        else if(t==2){ int u; cin>>u; cout<<h.querySubtreeSum(u) <<"\n"; }
        else if(t==3){ int u; cin>>u; cout<<h.querySubtreeMin(u) <<"\n"; }
        else if(t==4){ int u; cin>>u; cout<<h.querySubtreeMax(u) <<"\n"; }
        else if(t==5){ int u; cin>>u; cout<<h.querySubtreeGcd(u) <<"\n"; }
        else if(t==6){ int u; cin>>u; cout<<h.querySubtreeLcm(u) <<"\n"; }
        else if(t==7){ int u,v; cin>>u>>v; cout<<h.queryPathSum(u,v)<<"\n"; }
        else if(t==8){ int u,v; cin>>u>>v; cout<<h.queryPathMin(u,v)<<"\n"; }
        else if(t==9){ int u,v; cin>>u>>v; cout<<h.queryPathMax(u,v)<<"\n"; }
        else if(t==10){ int u,v; cin>>u>>v; cout<<h.queryPathGcd(u,v)<<"\n"; }
        else if(t==11){ int u,v; cin>>u>>v; cout<<h.queryPathLcm(u,v)<<"\n"; }
    }
    return 0;
}
#endif
